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
		/**
		 * @class	ModelGL
		 *
		 * @brief	A model gl.
		 */
		class ModelGL : public IModel
		{
		public:

			/**
			 * @fn	ModelGL::ModelGL();
			 *
			 * @brief	Default constructor.
			 */
			ModelGL();

			/**
			 * @fn	ModelGL::~ModelGL();
			 *
			 * @brief	Destructor.
			 */
			~ModelGL();

			/**
			 * @fn	void ModelGL::Render(IShader& shader);
			 *
			 * @brief	Renders the given shader.
			 *
			 * @param [in,out]	shader	The shader.
			 */
			void Render(IShader& shader);

			/**
			 * @fn	void ModelGL::Update();
			 *
			 * @brief	Updates this object.
			 */
			void Update();
		};
	}
}