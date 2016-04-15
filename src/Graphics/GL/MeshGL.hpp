/*
************************************
* Copyright (C) 2016 ByteForge
* MeshGL.hpp
************************************
*/

#pragma once
#include "../IMesh.hpp"
/*
#if __APPLE__
#include <OpenGL/gl.h>
#else
#include <windows.h>
#include <gl/GL.h>
#endif
*/
#include "flextGL.h"
#include "BufferGL.hpp"
#include <memory>

namespace anvil
{
	namespace GL
	{
		/**
		 * @class	MeshGL
		 *
		 * @brief	A mesh gl.
		 */
		class MeshGL : public IMesh
		{
		public:

			/**
			 * @fn	MeshGL::MeshGL();
			 *
			 * @brief	Default constructor.
			 */
			MeshGL();
			~MeshGL();

			/**
			 * @fn	void MeshGL::Render(IShader& shader);
			 *
			 * @brief	Renders the given shader.
			 *
			 * @param [in,out]	shader	The shader.
			 */
			void Render(IShader& shader);

			/**
			* @fn	virtual void IMesh::Init() = 0;
			*
			* @brief	Initializes the Mesh for rendering.
			*/
			void Init();

		private:
			GLuint m_vao;
			std::unique_ptr<Buffer> m_vbo, m_uvbo, m_nbo, m_fbo, m_mbo;
		};
	}
}