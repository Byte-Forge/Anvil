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
#include "../../Core/Options.hpp"
#include "../Camera.hpp"
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

	if (FLEXT_ARB_debug_output)
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageCallbackARB(debugCallback, nullptr);	//crashes on mac
	}

	//doesnt throw a exception on mac??
	if(!FLEXT_ARB_texture_storage)
		throw AnvilException("ARB_texture_storage not supported!", __FILE__, __LINE__);

	if(!FLEXT_EXT_texture_compression_s3tc)
		throw AnvilException("S3TC texture compression not supported!", __FILE__, __LINE__);

	m_matrix_data = MatrixData();
	m_matrix_ubo.Create();

	m_depth_matrix_data = DepthMatrixData();
	m_depth_matrix_ubo.Create();

	m_tessellation_data = TessellationData();
	m_tessellation_ubo.Create();

	m_light_data = LightData();
	m_light_ubo.Create();

	m_ubo_data = UboData();
	m_ubo.Create();

	m_skyboxShader = std::make_unique<GL::Shader>();
	m_skyboxShader->Load("shader/gl/skybox.vert", "shader/gl/skybox.frag");
	m_skyboxShader->AttachUBO("matrix_block", m_matrix_ubo.GetID());
	m_skyboxShader->AttachUBO("light_block", m_light_ubo.GetID());

	m_modelShader = std::make_unique<GL::Shader>();
	m_modelShader->Load("shader/gl/model.vert", "shader/gl/model.tesc", "shader/gl/model.tese", "shader/gl/model.geom", "shader/gl/model.frag");
	m_modelShader->AttachUBO("matrix_block", m_matrix_ubo.GetID());
	m_modelShader->AttachUBO("depth_matrix_block", m_depth_matrix_ubo.GetID());
	m_modelShader->AttachUBO("tessellation_block", m_tessellation_ubo.GetID());
	m_modelShader->AttachUBO("light_block", m_light_ubo.GetID());

	m_minimal_modelShader = std::make_unique<GL::Shader>();
	m_minimal_modelShader->Load("shader/gl/minimal_model.vert", "shader/gl/minimal_model.frag");
	m_minimal_modelShader->AttachUBO("matrix_block", m_matrix_ubo.GetID());

	m_shadow_modelShader = std::make_unique<GL::Shader>();
	m_shadow_modelShader->Load("shader/gl/shadow_model.vert", "shader/gl/shadow.frag");
	m_shadow_modelShader->AttachUBO("depth_matrix_block", m_depth_matrix_ubo.GetID());

	m_minimal_terrainShader = std::make_unique<GL::Shader>();
	m_minimal_terrainShader->Load("shader/gl/minimal_terrain.vert", "shader/gl/minimal_terrain.frag");
	m_minimal_terrainShader->AttachUBO("matrix_block", m_matrix_ubo.GetID());

	m_shadow_terrainShader = std::make_unique<GL::Shader>();
	m_shadow_terrainShader->Load("shader/gl/shadow_terrain.vert", "shader/gl/shadow.frag");
	m_shadow_terrainShader->AttachUBO("depth_matrix_block", m_depth_matrix_ubo.GetID());

	m_terrainShader = std::make_unique<GL::Shader>();
	m_terrainShader->Load("shader/gl/terrain.vert", "shader/gl/terrain.tesc", "shader/gl/terrain.tese", "shader/gl/terrain.geom", "shader/gl/terrain.frag");
	m_terrainShader->AttachUBO("matrix_block", m_matrix_ubo.GetID());
	m_terrainShader->AttachUBO("depth_matrix_block", m_depth_matrix_ubo.GetID());
	m_terrainShader->AttachUBO("tessellation_block", m_tessellation_ubo.GetID());
	m_terrainShader->AttachUBO("light_block", m_light_ubo.GetID());

	m_quadShader = std::make_unique<GL::Shader>();
	m_quadShader->Load("shader/gl/quad.vert", "shader/gl/quad.frag");

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
		//glGetIntegerv(VBO_FREE_MEMORY_ATI, vram); //invalid enum crash on amd gpu??
		m_totalVRAM = vram[0] / 1024;
	}
	else
		m_totalVRAM = 0;

	glm::vec2 res = Core::GetCore()->GetResolution();
	float sampleValue = Options::GetSampleFactor();
	m_shadowBuffer = std::make_unique<GL::FrameBuffer>(res * sampleValue);
	m_frameBuffer = std::make_unique<GL::FrameBuffer>(res * sampleValue);

	static const float quad_vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f
	};

	m_quad_vbo = std::make_unique<GL::Buffer>(GL::ARRAY_BUFFER);
	m_quad_vbo->Update(sizeof(quad_vertices), quad_vertices, GL::STATIC);

	m_biasMatrix = glm::mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

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

void RendererGL::Render()
{
	m_minimal_modelShader->Update();
	m_minimal_terrainShader->Update();
	m_terrainShader->Update();
	m_modelShader->Update();

	if (Options::GetMinimalRendering())
		m_lowSettings = true;
	else
		m_lowSettings = false;

	if (Options::GetSampleFactor() > 1)
		m_render2buffer = true;
	else
		m_render2buffer = false;

	if (Options::GetShadows())
		m_renderShadows = true;
	else
		m_renderShadows = false;

	m_rendered_polygons = 0;

	m_terrain->Update();

	glm::vec3 lightDir = glm::vec3(-0.0f, 3.0f, -3.0f);

	m_matrix_data.vp = Core::GetCore()->GetCamera()->GetViewProjectionMatrix();
	m_matrix_data.v = Core::GetCore()->GetCamera()->GetViewMatrix();
	m_matrix_ubo.Update(m_matrix_data);

	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-100, 100, -100, 100, 0.5, 1000.0);
	float distance = glm::length(Core::GetCore()->GetCamera()->GetPosition() - Core::GetCore()->GetCamera()->GetLookAt());
	glm::mat4 depthViewMatrix = glm::lookAt(lightDir * distance + Core::GetCore()->GetCamera()->GetLookAt(), Core::GetCore()->GetCamera()->GetLookAt(), glm::vec3(0, 1, 0));
	//glm::mat4 depthViewMatrix = glm::lookAt(lightDir, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0, 1, 0));

	m_depth_matrix_data.depth_vp = depthProjectionMatrix * depthViewMatrix;
	m_depth_matrix_data.depth_bias_vp = m_biasMatrix * depthProjectionMatrix * depthViewMatrix;
	m_depth_matrix_ubo.Update(m_depth_matrix_data);

	m_tessellation_data.tess_factor = GetTessfactor();
	m_tessellation_data.max_tess_factor = m_maxTesselation;
	m_tessellation_ubo.Update(m_tessellation_data);

	m_light_data.cameraPos = glm::vec4(Core::GetCore()->GetCamera()->GetPosition(), 1.0f);
	m_light_data.lightDir = glm::vec4(lightDir, 1.0f);
	glm::vec4 ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	m_light_data.ambient = ambient; 
	glm::vec4 diffuse = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
	m_light_data.diffuse = diffuse;
	glm::vec4 spec = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_light_data.spec = spec; 
	m_light_ubo.Update(m_light_data);

	JoinInstanceThreads();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/////////////////////////////////////////////// render scene to shadowbuffer /////////////////////////////////////////////////////////
	if (m_renderShadows && !m_lowSettings)
	{
		glEnable(GL_DEPTH_TEST);
		m_shadowBuffer->Bind();
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background
		Clear();

		m_shadow_terrainShader->Use();
		m_terrain->Render(*m_shadow_terrainShader, true);

		m_shadow_modelShader->Use();
		for (auto& renderable : m_renderables)
			renderable->Render(*m_shadow_modelShader, true); 
		glBindFramebuffer(GL_FRAMEBUFFER, 0); //unbind framebuffer
	}

	/////////////////////////////////////////////// render scene to framebuffer /////////////////////////////////////////////////////////
	if (m_render2buffer && !m_lowSettings)
		m_frameBuffer->Bind();

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background
	Clear();

	m_skyboxShader->Use();
	m_rendered_polygons += m_skybox->Render(*m_skyboxShader);

	if (m_lowSettings)
	{
		m_minimal_terrainShader->Use();
		m_rendered_polygons += m_terrain->Render(*m_minimal_terrainShader, true);

		m_minimal_modelShader->Use();
		for (auto& renderable : m_renderables)
			m_rendered_polygons += renderable->Render(*m_minimal_modelShader, true);
	}
	else
	{
		m_terrainShader->Use();
		if (m_renderShadows)
		{
			m_shadowBuffer->BindDepthTexture();
			glUniform1i(m_terrainShader->GetUniform("shadowMap"), 9);
		}
		glUniform1i(m_terrainShader->GetUniform("use_shadows"), m_renderShadows);
		m_rendered_polygons += m_terrain->Render(*m_terrainShader);

		m_modelShader->Use();
		if (m_renderShadows)
		{
			m_shadowBuffer->BindDepthTexture();
			glUniform1i(m_modelShader->GetUniform("shadowMap"), 9);
		}
		glUniform1i(m_modelShader->GetUniform("use_shadows"), m_renderShadows);
		for (auto& renderable : m_renderables)
			m_rendered_polygons += renderable->Render(*m_modelShader);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0); //unbind framebuffer

	UpdateInstances();

	if (m_render2buffer && !m_lowSettings)
	{
		/////////////////////////////////////////////// render framebuffer to quad /////////////////////////////////////////////////////////
		glm::vec2 res = Core::GetCore()->GetResolution();
		glViewport(0, 0, res.x, res.y);
		Clear();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		m_quadShader->Use();

		glActiveTexture(GL_TEXTURE0);
		m_frameBuffer->BindTexture();

		glEnableVertexAttribArray(0);
		m_quad_vbo->Bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
	}
}

void RendererGL::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
	float sampleValue = Options::GetSampleFactor();
	m_frameBuffer = std::make_unique<GL::FrameBuffer>(glm::vec2(width, height) * sampleValue);
	m_shadowBuffer = std::make_unique<GL::FrameBuffer>(glm::vec2(width, height) * sampleValue);
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