#include "TextureLoader.hpp"

#include <iostream>
#include <gli/gli.hpp>
#include <gli/texture.hpp>
#include <gli/load.hpp>
#include "../Graphics/GL/flextGL.h"
#include "../Graphics/GL/Texture.hpp"
#include "../Core/ResourceHandler.hpp"

using namespace std;
using namespace hpse;

void TextureLoader::Load(const std::string& name)
{
	cout << "loading texture: " << name << endl;
	std::string path = "textures/";
	std::string ext = ".ktx";

	GLuint m_handle;
	gli::texture Texture = gli::load(path + name + ext);
	if (Texture.empty())
	{
		m_handle = 0;
		return;
	}

	gli::gl GL;
	gli::gl::format const Format = GL.translate(Texture.format());
	GLenum Target = GL.translate(Texture.target());

	m_handle = 0;
	glGenTextures(1, &m_handle);
	glBindTexture(Target, m_handle);
	glTexParameteri(Target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(Target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(Texture.levels() - 1));
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_R, Format.Swizzles[0]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_G, Format.Swizzles[1]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_B, Format.Swizzles[2]);
	glTexParameteri(Target, GL_TEXTURE_SWIZZLE_A, Format.Swizzles[3]);

	glm::tvec3<GLsizei> const Dimensions(Texture.dimensions());
	GLsizei const FaceTotal = static_cast<GLsizei>(Texture.layers() * Texture.faces());

	int width = Dimensions.x;
	int height = Dimensions.y;

	switch (Texture.target())
	{
	case gli::TARGET_1D:
		#ifdef GL_ARB_texture_storage
		glTexStorage1D(Target, static_cast<GLint>(Texture.levels()), Format.Internal, Dimensions.x);
		#endif
		break;
	case gli::TARGET_1D_ARRAY:
	case gli::TARGET_2D:
	case gli::TARGET_CUBE:
		#ifdef GL_ARB_texture_storage
		glTexStorage2D(Target, static_cast<GLint>(Texture.levels()), Format.Internal, Dimensions.x, Texture.target() == gli::TARGET_2D ? Dimensions.y : FaceTotal);
		#endif
		break;
	case gli::TARGET_2D_ARRAY:
	case gli::TARGET_3D:
	case gli::TARGET_CUBE_ARRAY:
		#ifdef GL_ARB_texture_storage
		glTexStorage3D(Target, static_cast<GLint>(Texture.levels()), Format.Internal, Dimensions.x, Dimensions.y, Texture.target() == gli::TARGET_3D ? Dimensions.z : FaceTotal);
		#endif
		break;
	default:
		assert(0);
		break;
	}

	for (std::size_t Layer = 0; Layer < Texture.layers(); ++Layer)
	{
		for (std::size_t Face = 0; Face < Texture.faces(); ++Face)
		{
			for (std::size_t Level = 0; Level < Texture.levels(); ++Level)
			{
				GLsizei const LayerGL = static_cast<GLsizei>(Layer);
				glm::tvec3<GLsizei> Dimensions(Texture.dimensions(Level));
				Target = gli::is_target_cube(Texture.target()) ? static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + Face) : Target;

				switch (Texture.target())
				{
				case gli::TARGET_1D:
					if (gli::is_compressed(Texture.format()))
						glCompressedTexSubImage1D(Target, static_cast<GLint>(Level), 0, Dimensions.x,
							Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
							Texture.data(Layer, Face, Level));
					else
						glTexSubImage1D(Target, static_cast<GLint>(Level), 0, Dimensions.x,
							Format.External, Format.Type,
							Texture.data(Layer, Face, Level));
					break;
				case gli::TARGET_1D_ARRAY:
				case gli::TARGET_2D:
				case gli::TARGET_CUBE:
					if (gli::is_compressed(Texture.format()))
						glCompressedTexSubImage2D(Target, static_cast<GLint>(Level),
							0, 0,
							Dimensions.x,
							Texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : Dimensions.y,
							Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
							Texture.data(Layer, Face, Level));
					else
						glTexSubImage2D(Target, static_cast<GLint>(Level),
							0, 0,
							Dimensions.x,
							Texture.target() == gli::TARGET_1D_ARRAY ? LayerGL : Dimensions.y,
							Format.External, Format.Type,
							Texture.data(Layer, Face, Level));
					break;
				case gli::TARGET_2D_ARRAY:
				case gli::TARGET_3D:
				case gli::TARGET_CUBE_ARRAY:
					if (gli::is_compressed(Texture.format()))
						glCompressedTexSubImage3D(Target, static_cast<GLint>(Level),
							0, 0, 0,
							Dimensions.x, Dimensions.y,
							Texture.target() == gli::TARGET_3D ? Dimensions.z : LayerGL,
							Format.Internal, static_cast<GLsizei>(Texture.size(Level)),
							Texture.data(Layer, Face, Level));
					else
						glTexSubImage3D(
							Target, static_cast<GLint>(Level),
							0, 0, 0,
							Dimensions.x, Dimensions.y,
							Texture.target() == gli::TARGET_3D ? Dimensions.z : LayerGL,
							Format.External, Format.Type,
							Texture.data(Layer, Face, Level));
					break;
				default: 
					assert(0); 
					break;
				}
			}
		}
	}
	GL::Texture tex(m_handle);
	std::shared_ptr<IResource> p(&tex);
	ResourceHandler::instance()->AddResource(name, p);
}
