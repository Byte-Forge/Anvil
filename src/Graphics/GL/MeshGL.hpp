/*
************************************
* Copyright (C) 2016 ByteForge
* MeshGL.hpp
************************************
*/

#pragma once
#include "../IMesh.hpp"
#include "flextGL.h"
#include "BufferGL.hpp"
#include <memory>

namespace anvil
{
	namespace GL
	{
		class MeshGL : public IMesh
		{
		public:
			MeshGL();
			~MeshGL();

			void Update();
			void Render(int mode);

		private:
			GLuint m_vao;
			std::unique_ptr<Buffer> m_vbo, m_uvbo, m_nbo, m_fbo, m_mbo;
		};
	}
}