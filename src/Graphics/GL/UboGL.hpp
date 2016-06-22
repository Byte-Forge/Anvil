#pragma once
#include "flextGL.h"
#include <iostream>
#include <stdlib.h>

namespace anvil
{
	namespace GL
	{
		template<class T>
		class UniformBuffer
		{
		public:
			UniformBuffer() : m_ubo(0)
			{

			}

			~UniformBuffer()
			{
				if(m_ubo)
					glDeleteBuffers(1,&m_ubo);
				m_ubo = 0;
			}

			void Create()
			{
				glGenBuffers(1, &m_ubo);
			}

			void Update(const T& data)
			{
				glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
				glBufferData(GL_UNIFORM_BUFFER, sizeof(data), &data, GL_DYNAMIC_DRAW);
			}

			void Bind(const GLuint index)
			{
				glBindBufferBase(GL_UNIFORM_BUFFER, index, m_ubo);
			}

		private:
			GLuint m_ubo;
		};
	}
	
}