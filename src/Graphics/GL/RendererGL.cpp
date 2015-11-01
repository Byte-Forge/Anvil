#include "RendererGL.hpp"
#include "flextGL.h"
#include "Texture.hpp"
#include "Shader.hpp"
#include "../Types.hpp"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
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
    glDebugMessageCallbackARB(debugCallback,nullptr);
	#endif
    m_overlay = std::make_unique<GL::Texture>();
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
    m_guiShader = std::make_unique<GL::Shader>();
    m_guiShader->Load("./shader/gui.vs","./shader/gui.fs");
    m_guiShader->Compile();
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

void RendererGL::Render(glm::mat4& ortho)
{
    m_overlay->Bind();
	glUniformMatrix4fv(0,1,false,glm::value_ptr(ortho));
	glUseProgram(0);
}