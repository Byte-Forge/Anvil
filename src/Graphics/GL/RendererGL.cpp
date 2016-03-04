/*
************************************
* Copyright (C) 2016 ByteForge
* RendererGL.cpp
************************************
*/

#include "RendererGL.hpp"
#include "TextureGL.hpp"
#include "ShaderGL.hpp"
#include "../../Core.hpp"
#include "../IRenderable.hpp"
#include "../../Exception.hpp"
#include "../../Util/stb_image.h"
#include <iostream>

using namespace anvil;


std::map<std::string, IRenderer::Vendor> vendorMap = 
{	{"NVIDIA Corporation",IRenderer::NVIDIA},
	{"ATI Technologies Inc.",IRenderer::AMD} };

//NVIDIA
#define GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX          0x9047
#define GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX    0x9048
#define GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX  0x9049
#define GPU_MEMORY_INFO_EVICTION_COUNT_NVX            0x904A
#define GPU_MEMORY_INFO_EVICTED_MEMORY_NVX            0x904B

//AMD
#define VBO_FREE_MEMORY_ATI                     0x87FB
#define TEXTURE_FREE_MEMORY_ATI                 0x87FC
#define RENDERBUFFER_FREE_MEMORY_ATI            0x87FD

class GLGeometry
{
public:
	GLuint m_vbo, m_ibo, m_vao,m_texture;
	int m_numVerts;

	GLGeometry() : m_vbo(0), m_ibo(0), m_texture(0), m_numVerts(0),m_vao(0)
	{
	};

	~GLGeometry()
	{
		if (m_vao)
		{
			glDeleteVertexArrays(1, &m_vao);
			m_vao = 0;
		}		

		if (m_vbo)
		{
			glDeleteBuffers(1, &m_vbo);
			m_vbo = 0;
		}			

		if (m_ibo)
		{
			glDeleteBuffers(1, &m_ibo);
			m_ibo = 0;
		}			
	};
};

struct Vertex
{
	glm::vec2 Position, TexCoord;
	glm::vec4 Color;
};

#if 1
void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id,
                               GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	if (type == GL_DEBUG_TYPE_OTHER_ARB)
		return;

    std::cout << "--GL DEBUG--" << std::endl;
    std::cout << "Message: "<< message << std::endl;
    std::cout << "Type: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR_ARB:
			std::cout << "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
            std::cout << "DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
            std::cout << "UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY_ARB:
            std::cout << "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE_ARB:
            std::cout << "PERFORMANCE";
            break;
    }
    std::cout << std::endl;

    std::cout << "ID: " << id << std::endl;
    std::cout << "SEVERITY: ";
    switch (severity){
        case GL_DEBUG_SEVERITY_LOW_ARB:
            std::cout << "LOW";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM_ARB:
            std::cout << "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_HIGH_ARB:
            std::cout << "HIGH";
            break;
    }
    std::cout << std::endl;

	if (type == GL_DEBUG_TYPE_ERROR_ARB)
	{
		throw AnvilException("OpenGL Error, watch console for information", __FILE__, __LINE__);
	}
}
#endif

RendererGL::RendererGL() 
{
    flextInit();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	#if 1
	if (FLEXT_ARB_debug_output)
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
        glDebugMessageCallbackARB(debugCallback, nullptr);	//crashes on mac
	#endif

	//doesnt throw a exception on mac??
	if(!FLEXT_ARB_texture_storage)
		throw AnvilException("ARB_texture_storage not supported!", __FILE__, __LINE__);


	if(!FLEXT_EXT_texture_compression_s3tc)
		throw AnvilException("S3TC texture compression not supported!", __FILE__, __LINE__);


	m_guiShader = std::make_unique<GL::Shader>();
	m_guiShader->Load("shader/gl/gui.vert", "shader/gl/gui.frag");
	m_guiShader->Compile();

	m_guiShader->AddUniform("translation");
	m_guiShader->AddUniform("ortho");
	m_guiShader->AddUniform("tex");
	m_guiShader->AddUniform("useTex");

	m_skyboxShader = std::make_unique<GL::Shader>();
	m_skyboxShader->Load("shader/gl/skybox.vert", "shader/gl/skybox.frag");
	m_skyboxShader->Compile();

	m_skyboxShader->AddUniform("skybox");
	m_skyboxShader->AddUniform("mvp");
	m_skyboxShader->AddUniform("cameraPosition");

	for (unsigned int i = 0; i < m_shaderModes.size(); i++)
	{
		m_terrainShaders.push_back(std::make_unique<GL::Shader>());
		m_terrainShaders[i]->Define(m_shaderModes[i]);
		m_terrainShaders[i]->Load("shader/gl/terrain.vert", "shader/gl/terrain.tesc", "shader/gl/terrain.tese", "shader/gl/terrain.geom", "shader/gl/terrain.frag");
		m_terrainShaders[i]->Compile();

		m_terrainShaders[i]->AddUniform("albedoSampler");
		m_terrainShaders[i]->AddUniform("normalSampler");
		m_terrainShaders[i]->AddUniform("specularSampler");
		m_terrainShaders[i]->AddUniform("displacementSampler");
		m_terrainShaders[i]->AddUniform("ambientSampler");
		
		m_terrainShaders[i]->AddUniform("max_factor");
		m_terrainShaders[i]->AddUniform("tess_factor");

		m_terrainShaders[i]->AddUniform("m");
		m_terrainShaders[i]->AddUniform("v");
		m_terrainShaders[i]->AddUniform("mv3x3");
		m_terrainShaders[i]->AddUniform("mvp");

		m_terrainShaders[i]->AddUniform("lightPos");
	}

	m_vendor = OTHER;
	auto iterator = vendorMap.find(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	if (iterator != vendorMap.end())
		m_vendor = (*iterator).second;

	m_deviceName = (char*)glGetString(GL_RENDERER);
	if (m_vendor == NVIDIA)
	{
		glGetIntegerv(GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &m_totalVRAM);
		m_totalVRAM /= 1024;
	}	
	else if (m_vendor == AMD)
	{
		int vram[4];
		glGetIntegerv(VBO_FREE_MEMORY_ATI, vram);
		m_totalVRAM = vram[0] / 1024;
	}
	else
		m_totalVRAM = 0;

	Core::GetCore()->GetResources()->GetParticleSystem("test.json");
}

RendererGL::~RendererGL()
{	

}

void RendererGL::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT|
            GL_STENCIL_BUFFER_BIT|
            GL_DEPTH_BUFFER_BIT);
}

void RendererGL::Render(const glm::mat4& ortho)
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background
	m_skyboxShader->Use();
	m_skybox->Update();
	m_skybox->Render(*m_skyboxShader);

	glEnable(GL_DEPTH_TEST);

	m_terrain->Update();

	if (m_wireframeMode)
	{
		m_terrainShaders[1]->Use();		
		m_terrain->Render(*m_terrainShaders[1]);
	}
	else
	{
		m_terrainShaders[0]->Use();
		m_terrain->Render(*m_terrainShaders[0]);
	}
	if (m_normalsMode)
	{
		m_terrainShaders[2]->Use();
		m_terrain->Render(*m_terrainShaders[2]);
	}

	for (auto& renderable : m_renderables)
	{
		renderable->Update();
	}

	//apply entity shader here
    //for(auto& renderable : m_renderables)
    //   renderable->Render(0);

	glDisable(GL_DEPTH_TEST);
}

void RendererGL::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
}

void RendererGL::PrintInfo()
{
    char* vendor = (char*)glGetString(GL_VENDOR);
    std::cout << "GPU Vendor: " << vendor << std::endl;
	char* device = (char*)glGetString(GL_RENDERER);
	std::cout << "GPU Device: " << device << std::endl;
    char* version = (char*)glGetString(GL_VERSION);
    std::cout << "OpenGL Version: " << version << std::endl;
    char* glslversion = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "GLSL Version: " << glslversion << std::endl;
}

void RendererGL::RenderGeometry(Rocket::Core::Vertex * vertices, int num_vertices, int * indices,
	int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f & translation)
{
	Rocket::Core::CompiledGeometryHandle gh = CompileGeometry(vertices,
		num_vertices, indices, num_indices, texture);
	RenderCompiledGeometry(gh, translation);
	ReleaseCompiledGeometry(gh);
}

Rocket::Core::CompiledGeometryHandle RendererGL::CompileGeometry(Rocket::Core::Vertex * vertices, int num_vertices, int * indices, int num_indices, Rocket::Core::TextureHandle texture)
{
	std::vector<Vertex> data(num_vertices);

	for (unsigned long i = 0; i < data.size(); i++)
	{
		data[i].Position = *(glm::vec2*)&vertices[i].position;
		data[i].TexCoord = *(glm::vec2*)&vertices[i].tex_coord;
		data[i].Color = glm::vec4((float)vertices[i].colour.red / 255.f, (float)vertices[i].colour.green / 255.f, (float)vertices[i].colour.blue / 255.f, (float)vertices[i].colour.alpha / 255.f);
	};

	GLGeometry* geometry = new GLGeometry();
	geometry->m_numVerts = num_indices;

	glGenBuffers(1, &geometry->m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * num_vertices, &data[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &geometry->m_vao);
	glBindVertexArray(geometry->m_vao);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

	// UV
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));

	// Colors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

	glGenBuffers(1, &geometry->m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * num_indices, indices, GL_STATIC_DRAW);

	geometry->m_texture = texture;

	return Rocket::Core::CompiledGeometryHandle(geometry);
}

void RendererGL::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle handle, const Rocket::Core::Vector2f & translation)
{
	glActiveTexture(GL_TEXTURE0);
	m_guiShader->Use();

	GLGeometry* geometry = reinterpret_cast<GLGeometry*>(handle);
	glBindVertexArray(geometry->m_vao);
	glBindTexture(GL_TEXTURE_2D, geometry->m_texture);
	
	
	if (geometry->m_texture)
		glUniform1i(m_guiShader->GetUniform("useTex"), 1);
	else
		glUniform1i(m_guiShader->GetUniform("useTex"), 0);

	glUniform1i(m_guiShader->GetUniform("tex"), 0);
	
	glUniform2f(m_guiShader->GetUniform("translation"), translation.x, translation.y);
	auto* mat = glm::value_ptr(Core::GetCore()->GetGraphics()->GetOrtho());
	glUniformMatrix4fv(m_guiShader->GetUniform("ortho"), 1, GL_FALSE, mat);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_ibo);
	glDrawElements(GL_TRIANGLES, geometry->m_numVerts, GL_UNSIGNED_INT, nullptr);
	glDisable(GL_BLEND);
}

void RendererGL::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
	delete (GLGeometry*)geometry;
}

void RendererGL::EnableScissorRegion(bool enable)
{
	if (enable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

void RendererGL::SetScissorRegion(int x, int y, int width, int height)
{
	auto resolution = Core::GetCore()->GetResolution();
	glScissor(x, resolution.y - (y + height), width, height);
}

bool RendererGL::LoadTexture(Rocket::Core::TextureHandle & texture_handle, Rocket::Core::Vector2i & texture_dimensions, const Rocket::Core::String & source)
{
	Rocket::Core::FileInterface* file_interface = Rocket::Core::GetFileInterface();
	Rocket::Core::FileHandle file_handle = file_interface->Open(source);
	if (file_handle==0)
		return false;

	file_interface->Seek(file_handle, 0, SEEK_END);
	size_t buffer_size = file_interface->Tell(file_handle);
	file_interface->Seek(file_handle, 0, SEEK_SET);

	unsigned char* buffer = new unsigned char[buffer_size];
	file_interface->Read(buffer, buffer_size, file_handle);
	file_interface->Close(file_handle);

	unsigned char *data = stbi_load_from_memory(buffer, static_cast<int>(buffer_size), &texture_dimensions.x, &texture_dimensions.y, NULL, STBI_rgb_alpha);
	if (data == NULL)
		return false;

	GLuint handle = 0;
	glGenTextures(1, &handle);
	texture_handle = handle;
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_dimensions.x, texture_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(data);

	return true;
}

bool RendererGL::GenerateTexture(Rocket::Core::TextureHandle & texture_handle, const Rocket::Core::byte * source, const Rocket::Core::Vector2i & source_dimensions)
{
	GLuint handle = 0;
	glGenTextures(1, &handle);
	texture_handle = handle;
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, source_dimensions.x, source_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, source);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return true;
}

void RendererGL::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	glDeleteTextures(1, reinterpret_cast<GLuint*>(&texture_handle));
	texture_handle = 0;
}

const std::string RendererGL::GetGPUName()
{
	return m_deviceName;
}

int RendererGL::GetUsedVRAM()
{
	if (m_vendor == NVIDIA)
	{
		int vram = 0;
		glGetIntegerv(GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &vram);
		vram /= 1024;
		return m_totalVRAM - vram;
	}
	else if (m_vendor == AMD)
	{
		int vram[4];
		glGetIntegerv(VBO_FREE_MEMORY_ATI, vram); //is the same for texture, vbo and renderbuffer
		return m_totalVRAM - (vram[2] / 1024);
	}
	return 0;
}

int RendererGL::GetTotalVRAM()
{
	return m_totalVRAM;
}