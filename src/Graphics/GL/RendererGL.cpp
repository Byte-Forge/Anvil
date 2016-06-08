/*
************************************
* Copyright (C) 2016 ByteForge
* RendererGL.cpp
************************************
*/

#include "RendererGL.hpp"
#include "flextGL.h"
#include "TextureGL.hpp"
#include "ShaderGL.hpp"
#include "../../Core.hpp"
#include "../../Core/ResourceHandler.hpp"
#include "../IRenderable.hpp"
#include "../../Exception.hpp"
#include "../../Util/stb_image.h"
#include "../../Graphics.hpp"
#include <iostream>
#include <future>
#include <glm/gtc/type_ptr.hpp>

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

	m_skyboxShader = std::make_unique<GL::Shader>();
	m_skyboxShader->Load("shader/gl/skybox.vert", "shader/gl/skybox.frag");
	m_skyboxShader->Compile();

	m_modelShaders.push_back(std::make_unique<GL::Shader>());
	m_modelShaders[0]->Load("shader/gl/model.vert", "shader/gl/model.frag");
	m_modelShaders[0]->Compile();

	for (unsigned int i = 0; i < m_shaderModes.size(); i++)
	{
		m_terrainShaders.push_back(std::make_unique<GL::Shader>());
		m_terrainShaders[i]->Define(m_shaderModes[i]);
		m_terrainShaders[i]->Load("shader/gl/terrain.vert", "shader/gl/terrain.tesc", "shader/gl/terrain.tese", "shader/gl/terrain.geom", "shader/gl/terrain.frag");
		m_terrainShaders[i]->Compile();
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

	Core::GetCore()->GetResources()->GetParticleSystem("particle/test.json");
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
	m_rendered_polygons = 0;

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background
	m_skyboxShader->Use();
	m_skybox->Update();
	m_rendered_polygons += m_skybox->Render(*m_skyboxShader);

	glEnable(GL_DEPTH_TEST);

	m_terrain->Update();

	if (m_wireframeMode)
	{
		m_terrainShaders[1]->Use();		
		m_rendered_polygons += m_terrain->Render(*m_terrainShaders[1]);
	}
	else
	{
		m_terrainShaders[0]->Use();
		m_rendered_polygons += m_terrain->Render(*m_terrainShaders[0]);
	}
	if (m_normalsMode)
	{
		m_terrainShaders[2]->Use();
		m_rendered_polygons += m_terrain->Render(*m_terrainShaders[2]);
	}

	for (auto& entity : m_entities)
		entity->Update();

	m_modelShaders[0]->Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE); //we should not need this

    for (auto& renderable : m_renderables)
		m_rendered_polygons += renderable->Render(*m_modelShaders[0]);

	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);

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