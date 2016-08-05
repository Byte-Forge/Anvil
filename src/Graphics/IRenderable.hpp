/*
************************************
* Copyright (C) 2016 ByteForge
* IRenderable.hpp
************************************
*/

#pragma once
#include "IShader.hpp"

namespace anvil
{
	/**
	 * @class	IRenderable
	 *
	 * @brief	Interface implemented by each object that is drawn on screen.
	 */
	class IRenderable
	{
	public:

		/**
		 * @fn	virtual int IRenderable::Render(const IShader& shader, bool minimal) = 0;
		 *
		 * @brief	Renders the object.

		 * @param	shader	The shader.
		 * 					
		 * @param	minimal if it should render with minimal requirements
		 *
		 * @return returns the number of drawn polygons
		 */
		virtual size_t Render(IShader& shader, bool minimal = false) = 0;

		/**
		 * @fn	virtual void IRenderable::Update() = 0;
		 *
		 * @brief	Updates this object.
		 */
		virtual void Update() = 0;
	};
}