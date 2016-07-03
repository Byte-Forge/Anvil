/*
************************************
* Copyright (C) 2016 ByteForge
* Skybox.hpp
************************************
*/

#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "../ITexture.hpp"
#include "flextGL.h"
#include "../IRenderable.hpp"
#include "BufferGL.hpp"


namespace anvil
{
	namespace GL
	{
		/**
		 * @class	Skybox
		 *
		 * @brief	A skybox.
		 */
		class Skybox : public IRenderable
		{
		public:

			/**
			 * @fn	Skybox::Skybox();
			 *
			 * @brief	Default constructor.
			 */
			Skybox();

			/**
			 * @fn	Skybox::~Skybox();
			 *
			 * @brief	Destructor.
			 */
			~Skybox();

			/**
			 * @fn	void Skybox::Render(IShader& shader, bool minimal);
			 *
			 * @brief	Renders the given shader.
			 *
			 * @param [in,out]	shader	The shader.
			 * @param	minimal if it should render with minimal settings
			 *
			 * @return returns the number of drawn polygons
			 */
			int Render(IShader& shader, bool minimal);

			/**
			 * @fn	void Skybox::Update();
			 *
			 * @brief	Updates this object.
			 */
			void Update();

		private:
			std::shared_ptr<ITexture> m_diff;

			std::vector<glm::vec3> m_vertices;
			std::vector<std::uint32_t> m_faces;

			GLuint m_vao;
			std::unique_ptr<Buffer> m_vbo;
			std::unique_ptr<Buffer> m_fbo;
		};
	}
}