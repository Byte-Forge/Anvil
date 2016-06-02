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
		 * @fn	virtual int IRenderable::Render(int mode,const IShader& shader) = 0;
		 *
		 * @brief	Renders the given mode.
		 *
		 * @param	mode  	The mode.
		 * @param	shader	The shader.
		 *
		 * @return returns the number of drawn polygons
		 */
		virtual int Render(IShader& shader) = 0;

		/**
		 * @fn	virtual void IRenderable::Update() = 0;
		 *
		 * @brief	Updates this object.
		 */
		virtual void Update() = 0;
	};
}