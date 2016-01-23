#pragma once

namespace hpse
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
			~Buffer();

			void Bind();
			void Update(unsigned int bufferSize, const void* data, DrawType draw = STATIC);

		private:
			unsigned int m_handle;
			BufferType m_type;
		};
	}
}