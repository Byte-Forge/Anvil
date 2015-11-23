//
// Created by stephan on 27.10.15.
//

#include "flextGL.h"
#include "Texture.hpp"
#include <string>
#include <iostream>
using namespace hpse;

//is used to create a simple texture for the gui
GL::Texture::Texture()
{
	glGenTextures(1, &m_handle);
	glBindTexture(GL_TEXTURE_2D, m_handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void GL::Texture::Load(const gli::texture &tex)
{
	if(FLEXT_ARB_texture_storage)
	{
		std::cout << "Not supporting ARB_textrue_storage" << std::endl;
		return;
	}

	gli::gl GL;
	gli::gl::format const Format = GL.translate(tex.format());
	GLenum Target = GL.translate(tex.target());

	glTexParameteri(Target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(Target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(tex.levels() - 1));
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_R, Format.Swizzles[0]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_G, Format.Swizzles[1]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_B, Format.Swizzles[2]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_A, Format.Swizzles[3]);

	glm::tvec3<GLsizei> const Dimensions(tex.dimensions());
	GLsizei const FaceTotal = static_cast<GLsizei>(tex.layers() * tex.faces());

	int width = Dimensions.x;
	int height = Dimensions.y;


	switch (tex.target())
	{
		case gli::TARGET_1D:
			glTexStorage1D(Target, static_cast<GLint>(tex.levels()), Format.Internal, Dimensions.x);
			break;
		case gli::TARGET_1D_ARRAY:
		case gli::TARGET_2D:
		case gli::TARGET_CUBE:
			glTexStorage2D(Target, static_cast<GLint>(tex.levels()), Format.Internal, Dimensions.x, tex.target() == gli::TARGET_2D ? Dimensions.y : FaceTotal);
			break;
		case gli::TARGET_2D_ARRAY:
		case gli::TARGET_3D:
		case gli::TARGET_CUBE_ARRAY:
			glTexStorage3D(Target, static_cast<GLint>(tex.levels()), Format.Internal, Dimensions.x, Dimensions.y, tex.target() == gli::TARGET_3D ? Dimensions.z : FaceTotal);
			break;
		default:
			assert(0);
			break;
	}

	for (std::size_t Layer = 0; Layer < tex.layers(); ++Layer)
	{
		for (std::size_t Face = 0; Face < tex.faces(); ++Face)
		{
			for (std::size_t Level = 0; Level < tex.levels(); ++Level)
			{
				GLsizei const LayerGL = static_cast<GLsizei>(Layer);
				glm::tvec3<GLsizei> Dimensions(tex.dimensions(Level));
				Target = gli::is_target_cube(tex.target()) ? static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + Face) : Target;

				switch (tex.target())
				{
					case gli::TARGET_1D:
						if (gli::is_compressed(tex.format()))
							glCompressedTexSubImage1D(Target, static_cast<GLint>(Level), 0, Dimensions.x,
													  Format.Internal, static_cast<GLsizei>(tex.size(Level)),
													  tex.data(Layer, Face, Level));
						else
							glTexSubImage1D(Target, static_cast<GLint>(Level), 0, Dimensions.x,
											Format.External, Format.Type,
											tex.data(Layer, Face, Level));
						break;
					case gli::TARGET_1D_ARRAY:
					case gli::TARGET_2D:
					case gli::TARGET_CUBE:
						if (gli::is_compressed(tex.format()))
							glCompressedTexSubImage2D(Target, static_cast<GLint>(Level),
													  0, 0,
													  Dimensions.x,
													  tex.target() == gli::TARGET_1D_ARRAY ? LayerGL : Dimensions.y,
													  Format.Internal, static_cast<GLsizei>(tex.size(Level)),
													  tex.data(Layer, Face, Level));
						else
							glTexSubImage2D(Target, static_cast<GLint>(Level),
											0, 0,
											Dimensions.x,
											tex.target() == gli::TARGET_1D_ARRAY ? LayerGL : Dimensions.y,
											Format.External, Format.Type,
											tex.data(Layer, Face, Level));
						break;
					case gli::TARGET_2D_ARRAY:
					case gli::TARGET_3D:
					case gli::TARGET_CUBE_ARRAY:
						if (gli::is_compressed(tex.format()))
							glCompressedTexSubImage3D(Target, static_cast<GLint>(Level),
													  0, 0, 0,
													  Dimensions.x, Dimensions.y,
													  tex.target() == gli::TARGET_3D ? Dimensions.z : LayerGL,
													  Format.Internal, static_cast<GLsizei>(tex.size(Level)),
													  tex.data(Layer, Face, Level));
						else
							glTexSubImage3D(
									Target, static_cast<GLint>(Level),
									0, 0, 0,
									Dimensions.x, Dimensions.y,
									tex.target() == gli::TARGET_3D ? Dimensions.z : LayerGL,
									Format.External, Format.Type,
									tex.data(Layer, Face, Level));
						break;
					default:
						assert(0);
						break;
				}
			}
		}
	}
}

GL::Texture::~Texture()
{
    glDeleteTextures(1, &m_handle);
}

void GL::Texture::Update(int width, int height, const uint8_t *data)
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
}

void GL::Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
}


