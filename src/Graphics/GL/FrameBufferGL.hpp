/*
************************************
* Copyright (C) 2016 ByteForge
* FrameBufferGL.hpp
************************************
*/

#pragma once
#include "flextGL.h"
#include <glm/glm.hpp>
#include <memory>

namespace anvil
{
	namespace GL
	{
		/**
		* @class	FrameBuffer
		*
		* @brief	
		*/
		class FrameBuffer
		{
		public:
			/**
			* @fn	FrameBuffer::FrameBuffer();
			*
			* @brief	Constructor
			*/
			FrameBuffer();

			/**
			* @fn	FrameBuffer::FrameBuffer(glm::vec2 size);
			*
			* @brief	This will call glGenBuffer 
			* @param	size	the resolution of the framebuffer
			*/
			FrameBuffer(glm::vec2 size);

			/**
			* @fn	FrameBuffer::~FrameBuffer();
			*
			* @brief	Delete the internal frameBuffer object
			*/
			~FrameBuffer();

			/**
			* @fn	void FrameBuffer::Bind();
			*
			* @brief	Binds this object.
			*/
			void Bind();

			void BindTexture();

			/**
			* @fn	void FrameBuffer::Resize(glm::vec2 size);
			*
			* @brief	Resize the framebuffer to the given resolution.
			* @param	size	the new resolution
			*/
			void Resize(glm::vec2 size);

		private:
			glm::vec2 m_size;
			unsigned int m_handle;
			unsigned int m_texture_handle;
			unsigned int m_render_handle;
		};
	}
}