//
// Created by stephan on 27.10.15.
//

#include "flextGL.h"
#include "Texture.hpp"

using namespace hpse;

GL::Texture::Texture()
{
    glGenTextures(1,&m_handle);
}

GL::Texture::Texture(int width,int height)
{
    glGenTextures(1,&m_handle);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA8,GL_UNSIGNED_BYTE,NULL);
}

GL::Texture::~Texture()
{
    glDeleteTextures(1,&m_handle);
}

void GL::Texture::Update(int width,int height,const uint8_t *data)
{
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA8,GL_UNSIGNED_BYTE,data);
}

void GL::Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D,m_handle);
}