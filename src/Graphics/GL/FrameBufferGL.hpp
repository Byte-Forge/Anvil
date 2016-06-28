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
#include "TextureGL.hpp"

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

			/**
			* @fn	void FrameBuffer::Valid();
			*
			* @brief	Checks if the framebuffer is valid;
			*/
			bool Valid();

			void AttachTexture();

			inline std::shared_ptr<GL::Texture> GetTexture() { return m_texture; }

		private:
			glm::vec2 m_size;
			unsigned int m_handle;
			std::shared_ptr<GL::Texture> m_texture;
		};
	}
}