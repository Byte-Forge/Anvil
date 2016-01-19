#include "RendererGL.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "../Types.hpp"
#include "../../Core.hpp"
#include "../IRenderable.hpp"
#include "../../Exception.hpp"
#include "../../Util/stb_image.h"
#include <iostream>

using namespace hpse;

#ifndef NDEBUG
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
		throw HpseException("OpenGL Error, watch console for information", __FILE__, __LINE__);
	}
}
#endif

RendererGL::RendererGL()
{
    flextInit();
	
	#ifndef NDEBUG
    if(FLEXT_ARB_debug_output)
        glDebugMessageCallbackARB(debugCallback, nullptr);
	#endif

	if(!FLEXT_ARB_texture_storage)
		throw HpseException("ARB_texture_storage not supported!", __FILE__, __LINE__);

	if(!FLEXT_ARB_texture_compression_bptc)
		throw HpseException("BPTC texture compression not supported!", __FILE__, __LINE__);


	m_guiShader = std::make_unique<GL::Shader>();
	m_guiShader->Load("shader/gui.vert", "shader/gui.frag");
	m_guiShader->Compile();
	m_guiShader->Use();

	m_skyboxShader = std::make_unique<GL::Shader>();
	m_skyboxShader->Load("shader/skybox.vert", "shader/skybox.frag");
	m_skyboxShader->Compile();
	m_skyboxShader->Use();

	m_terrainShader = std::make_unique<GL::Shader>();
	m_terrainShader->Load("shader/terrain.vert", "shader/terrain.tess", "shader/terrain.eval", "shader/terrain.geo", "shader/terrain.frag");
	m_terrainShader->Compile();
	m_terrainShader->Use();
}

RendererGL::~RendererGL()
{	
	if(m_guiVao)
	{
		glDeleteVertexArrays(1, &m_guiVao);
		m_guiVao = 0;
	}
	
	if (m_guiVbo)
	{
		glDeleteBuffers(1, &m_guiVbo);
		m_guiVbo = 0;
	}
	
	if (m_guiIbo)
	{
		glDeleteBuffers(1, &m_guiIbo);
		m_guiIbo = 0;
	}	
}

void RendererGL::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT|
            GL_STENCIL_BUFFER_BIT|
            GL_DEPTH_BUFFER_BIT);
}

void RendererGL::Render(glm::mat4& ortho)
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background
	
	m_skyboxShader->Use();
	m_skybox->Update();
	m_skybox->Render();

	glEnable(GL_DEPTH_TEST);

	m_terrainShader->Use();
	m_terrain->Update();
	m_terrain->Render();

	/*
    for(auto& renderable : m_renderables)
        renderable->Update();
	
    for(auto& renderable : m_renderables)
        renderable->Render();
	*/

	glDisable(GL_DEPTH_TEST);

	//RenderGUI();
}

void RendererGL::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
}

void RendererGL::PrintInfo()
{
    char* vendor = (char*)glGetString(GL_VENDOR);
    std::cout << "GPU Vendor: " << vendor << std::endl;
    char* version = (char*)glGetString(GL_VERSION);
    std::cout << "OpenGL Version: " << version << std::endl;
    char* glslversion = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "GLSL Version: " << glslversion << std::endl;
}

class GLGeometry
{
public:
	GLuint m_vbo, m_ibo, m_texture;
	int m_numVerts;

	GLGeometry() : m_vbo(0), m_ibo(0)
	{
	};

	~GLGeometry()
	{
		if (m_vbo)
			glDeleteBuffers(1, &m_vbo);

		if (m_ibo)
			glDeleteBuffers(1, &m_ibo);

		m_vbo = m_ibo = 0;
	};
};

struct Vertex
{
	glm::vec2 Position, TexCoord;
	glm::vec4 Color;
};


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
		data[i].Color = glm::vec4((float)vertices[i].colour.red / 255.f,
			(float)vertices[i].colour.green / 255.f,
			(float)vertices[i].colour.blue / 255.f,
			(float)vertices[i].colour.alpha / 255.f);
	};

	GLGeometry* geometry = new GLGeometry();
	geometry->m_numVerts = num_indices;

	glGenBuffers(1, &geometry->m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * num_vertices, &data[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &geometry->m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * num_indices, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	geometry->m_texture = texture;

	return Rocket::Core::CompiledGeometryHandle(geometry);
}

void RendererGL::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle handle, const Rocket::Core::Vector2f & translation)
{
	m_guiShader->Use();
	auto translID = static_cast<GLuint>(m_guiShader->GetUniformLocation("translation"));
	auto orthoID = static_cast<GLuint>(m_guiShader->GetUniformLocation("ortho"));
	auto samplerID = static_cast<GLuint>(m_guiShader->GetUniformLocation("tex"));

	GLGeometry* geometry = reinterpret_cast<GLGeometry*>(handle);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vbo);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT,
		GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

	// UV
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT,
		GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));

	// Colors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT,
		GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_ibo);
	glBindTexture(GL_TEXTURE_2D, geometry->m_texture);

	glUniform1i(samplerID, 0);
	glUniform2f(translID, translation.x, translation.y);
	auto* mat = glm::value_ptr(Core::GetCore()->GetGraphics()->GetOrtho());
	glUniformMatrix4fv(orthoID, 1, GL_FALSE, mat);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, geometry->m_numVerts, GL_UNSIGNED_INT, nullptr);
	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
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
	auto* window = Core::GetCore()->GetWindow();
	glScissor(x, window->getSize().y - (y + height), width, height);
}

bool RendererGL::LoadTexture(Rocket::Core::TextureHandle & texture_handle, Rocket::Core::Vector2i & texture_dimensions, const Rocket::Core::String & source)
{
	Rocket::Core::FileInterface* file_interface = Rocket::Core::GetFileInterface();
	Rocket::Core::FileHandle file_handle = file_interface->Open(source);
	if (file_handle == NULL)
		return false;

	file_interface->Seek(file_handle, 0, SEEK_END);
	size_t buffer_size = file_interface->Tell(file_handle);
	file_interface->Seek(file_handle, 0, SEEK_SET);

	unsigned char* buffer = new unsigned char[buffer_size];
	file_interface->Read(buffer, buffer_size, file_handle);
	file_interface->Close(file_handle);


	unsigned char *data = stbi_load_from_memory(buffer, buffer_size, &texture_dimensions.x, &texture_dimensions.y, NULL, 0);
	if (data == NULL)
		return false;

	GLuint handle = 0;
	glGenTextures(1, &handle);
	texture_handle = handle;
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_dimensions.x, texture_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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

	return true;
}

void RendererGL::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	glDeleteTextures(1, &texture_handle);
	texture_handle = 0;
}

