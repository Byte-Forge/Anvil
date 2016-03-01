/*
************************************
* Copyright (C) 2016 ByteForge
* Buffer.hpp
************************************
*/

#pragma once

namespace anvil
{
	namespace GL
	{
		enum BufferType
		{
			ARRAY_BUFFER = 0x8892,
			ELEMENT_ARRAY_BUFFER = 0x8893
		};

		enum DrawType
		{
			STATIC = 0x88E4,
			DYNAMIC = 0x88E8,
			STREAM = 0x88E0  
		};

		class Buffer
		{
		public:
			Buffer(BufferType type = ARRAY_BUFFER);
			Buffer(const Buffer& that) = delete;
			~Buffer();

			Buffer & operator=(const Buffer&) = delete;

			void Bind();
			void Update(size_t bufferSize, const void* data, DrawType draw = STATIC);

		private:
			unsigned int m_handle;
			BufferType m_type;
		};
	}
}