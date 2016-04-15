/*
************************************
* Copyright (C) 2016 ByteForge
* Buffer.hpp
************************************
*/
#pragma once
#include <stdlib.h>

namespace anvil
{
	namespace GL
	{
		/**
		 * @enum	BufferType
		 *
		 * @brief	Values that represent buffer types.
		 */
		enum BufferType
		{
			ARRAY_BUFFER = 0x8892,
			ELEMENT_ARRAY_BUFFER = 0x8893
		};

		/**
		 * @enum	DrawType
		 *
		 * @brief	Values that represent draw types.
		 */
		enum DrawType
		{
			STATIC = 0x88E4,
			DYNAMIC = 0x88E8,
			STREAM = 0x88E0  
		};

		/**
		 * @class	Buffer
		 *
		 * @brief	An opengl buffer class that applies the RAII idiom to opengl buffers. Non copyable
		 */
		class Buffer
		{
		public:

			/**
			 * @fn	Buffer::Buffer(BufferType type = ARRAY_BUFFER);
			 *
			 * @brief	This will call glGenBuffer and by default create an array buffer
			 *
			 * @param	type	The buffer typem by default ARRAY_BUFFER
			 */
			Buffer(BufferType type = ARRAY_BUFFER);
			Buffer(const Buffer& that) = delete;

			/**
			 * @fn	Buffer::~Buffer();
			 *
			 * @brief	Delete the internal buffer object
			 */
			~Buffer();

			Buffer & operator=(const Buffer&) = delete;

			/**
			 * @fn	void Buffer::Bind();
			 *
			 * @brief	Binds this object.
			 */
			void Bind();

			/**
			 * @fn	void Buffer::Update(size_t bufferSize, const void* data, DrawType draw = STATIC);
			 *
			 * @brief	Updates this object.
			 *
			 * @param	bufferSize	Size of the buffer.
			 * @param	data	  	The data that will be uploaded to the buffer object
			 * @param	draw	  	What kind of buffer is this? By default this is STATIC
			 */
			void Update(size_t bufferSize, const void* data, DrawType draw = STATIC);

		private:
			unsigned int m_handle;
			BufferType m_type;
		};
	}
}