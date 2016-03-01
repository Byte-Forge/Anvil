/*
************************************
* Copyright (C) 2016 ByteForge
* ModelGL.hpp
************************************
*/

#pragma once
#include "../IModel.hpp"

namespace anvil
{
	namespace GL
	{
		class ModelGL : public IModel
		{
		public:
			ModelGL();
			~ModelGL();

			void Render(int mode);
			void Update();
		};
	}
}