#include "RendererGL.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "../Types.hpp"
#include "../../Core.hpp"
#include "../IRenderable.hpp"
#include <iostream>

using namespace hpse;

#ifndef NDEBUG
void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id,
                               GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
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
        case GL_DEBUG_TYPE_OTHER_ARB:
            std::cout << "OTHER";
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
}
#endif

RendererGL::RendererGL()
{
    flextInit();

	#ifndef NDEBUG
    if(FLEXT_ARB_debug_output)
        glDebugMessageCallbackARB(debugCallback, nullptr);
	#endif
    m_overlay = std::make_unique<GL::Texture>();

	m_guiShader = std::make_unique<GL::Shader>();
	m_guiShader->Load("./shader/gui.vs", "./shader/gui.fs");
	m_guiShader->Compile();
	m_guiShader->Use();
    SetupGUI();

	m_terrainShader = std::make_unique<GL::Shader>();
	//m_terrainShader->Load("./shader/terrain_dis.vs", "./shader/terrain_dis.tcs", "./shader/terrain_dis.tes", "./shader/terrain_dis.gs", "./shader/terrain_dis.fs");
	m_terrainShader->Load("./shader/terrain.vs", "./shader/terrain.fs");
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
    glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background
	
	m_terrainShader->Use();

    for(auto& renderable : m_renderables)
        renderable->Update();

	
    for(auto& renderable : m_renderables)
        renderable->Render();

	RenderGUI();
}

void RendererGL::RenderGUI()
{
	glDisable(GL_DEPTH_TEST);
	m_guiShader->Use();

	glActiveTexture(GL_TEXTURE0);
	m_overlay->Bind();

	glBindVertexArray(m_guiVao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_guiVbo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_guiIbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void RendererGL::SetupGUI()
{
    glGenVertexArrays(1, &m_guiVao);
    glBindVertexArray(m_guiVao);

    float vertices[16] = { -1.0,-1.0,0.0,1.0,
                            1.0,-1.0,1.0,1.0,
                           -1.0, 1.0,0.0,0.0,
                            1.0, 1.0,1.0,0.0};

    glGenBuffers(1, &m_guiVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_guiVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint elements[] = {
            0, 1, 2,
            2, 3, 1
    };

    glGenBuffers(1, &m_guiIbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_guiIbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
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

