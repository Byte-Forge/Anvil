//
// Created by stephan on 27.10.15.
//

#include "flextGL.h"
#include "Texture.hpp"
#include <string>
#include <iostream>
using namespace hpse;

gli::gl GL::Texture::GL;

bool GL::Texture::Load(std::vector<gli::texture> textures)
{
	m_target = GL_TEXTURE_2D_ARRAY;
	int max_size = 0;
	gli::gl::format const Format = GL.translate(textures[0].format());

	for (int i = 0; i < textures.size(); i++)
	{
		glm::tvec3<GLsizei> const Dimensions(textures[i].dimensions());
		if (Dimensions.x > max_size)
			max_size = Dimensions.x;
	}

	glGenTextures(1, &m_handle);
	glBindTexture(m_target, m_handle);
	glTexParameteri(m_target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(m_target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(textures[0].levels() - 1));
	glTexParameteri(m_target, GL_TEXTURE_SWIZZLE_R, Format.Swizzle[0]);
	glTexParameteri(m_target, GL_TEXTURE_SWIZZLE_G, Format.Swizzle[1]);
	glTexParameteri(m_target, GL_TEXTURE_SWIZZLE_B, Format.Swizzle[2]);
	glTexParameteri(m_target, GL_TEXTURE_SWIZZLE_A, Format.Swizzle[3]);

	glTexStorage3D(m_target, textures[0].levels(), Format.Internal, max_size, max_size, textures.size());

	for (int i = 0; i < textures.size(); i++)
	{
		for (std::size_t Layer = 0; Layer < textures[i].layers(); ++Layer)
		{
			for (std::size_t Face = 0; Face < textures[i].faces(); ++Face)
			{
				for (std::size_t Level = 0; Level < textures[i].levels(); ++Level)
				{
					glm::tvec3<GLsizei> Dimensions(textures[i].dimensions(Level));

					if (gli::is_compressed(textures[i].format()))
						glCompressedTexSubImage3D(m_target, static_cast<GLint>(Level),
							0, 0, i,
							Dimensions.x, Dimensions.y,
							1,
							Format.Internal, static_cast<GLsizei>(textures[i].size(Level)),
							textures[i].data(Layer, Face, Level));
					else
						glTexSubImage3D(m_target, static_cast<GLint>(Level),
							0, 0, i,
							Dimensions.x, Dimensions.y,
							1,
							Format.External, Format.Type,
							textures[i].data(Layer, Face, Level));
				}
			}
		}
	}
	return true;
}

bool GL::Texture::Load(const gli::texture &tex)
{
	gli::gl GL;
	gli::gl::format const Format = GL.translate(tex.format());
	m_target = GL.translate(tex.target());

	glGenTextures(1, &m_handle);
	glBindTexture(m_target, m_handle);
	glTexParameteri(m_target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(m_target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(tex.levels() - 1));
	glTexParameteri(m_target, GL_TEXTURE_SWIZZLE_R, Format.Swizzle[0]);
	glTexParameteri(m_target, GL_TEXTURE_SWIZZLE_G, Format.Swizzle[1]);
	glTexParameteri(m_target, GL_TEXTURE_SWIZZLE_B, Format.Swizzle[2]);
	glTexParameteri(m_target, GL_TEXTURE_SWIZZLE_A, Format.Swizzle[3]);

	glm::tvec3<GLsizei> const Dimensions(tex.dimensions());
	GLsizei const FaceTotal = static_cast<GLsizei>(tex.layers() * tex.faces());

	int width = Dimensions.x;
	int height = Dimensions.y;
	
	switch (tex.target())
	{
		case gli::TARGET_1D:
			glTexStorage1D(m_target, static_cast<GLint>(tex.levels()), Format.Internal, Dimensions.x);
			break;
		case gli::TARGET_1D_ARRAY:
		case gli::TARGET_2D:
		case gli::TARGET_CUBE:
			glTexStorage2D(m_target, static_cast<GLint>(tex.levels()), Format.Internal, Dimensions.x, tex.target() == gli::TARGET_2D ? Dimensions.y : FaceTotal);
			break;
		case gli::TARGET_2D_ARRAY:
		case gli::TARGET_3D:
		case gli::TARGET_CUBE_ARRAY:
			glTexStorage3D(m_target, static_cast<GLint>(tex.levels()), Format.Internal, Dimensions.x, Dimensions.y, tex.target() == gli::TARGET_3D ? Dimensions.z : FaceTotal);
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
				GLenum Target = m_target;
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
	return true;
}

GL::Texture::~Texture()
{
    glDeleteTextures(1, &m_handle);
}

void GL::Texture::Bind()
{
    glBindTexture(m_target, m_handle);
}




