/*
************************************
* Copyright (C) 2016 ByteForge
* IShader.hpp
************************************
*/

#pragma once
#include <string>
#include <map>
namespace anvil
{
    /**
     * @class	IShader
     *
     * @brief	Interface for OpenGL and Vulcan shaders.
     */
    class IShader
    {
    public:

        /**
         * @fn	virtual void IShader::Load(const std::string& vertShader, const std::string& fragShader) = 0;
         *
         * @brief	Loads.
         *
         * @param	vertShader	The vertical shader.
         * @param	fragShader	The fragment shader.
         */
        virtual void Load(const std::string& vertShader, const std::string& fragShader) = 0;

        /**
         * @fn	virtual void IShader::Load(const std::string& vertShader, const std::string& geoShader, const std::string& fragShader) = 0;
         *
         * @brief	Loads.
         *
         * @param	vertShader	The vertical shader.
         * @param	geoShader 	The geo shader.
         * @param	fragShader	The fragment shader.
         */
        virtual void Load(const std::string& vertShader, const std::string& geoShader, const std::string& fragShader) = 0;

		/**
		 * @fn	virtual void IShader::Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& fragShader) = 0;
		 *
		 * @brief	Loads.
		 *
		 * @param	vertShader		 	The vertical shader.
		 * @param	tessControlShader	The tess control shader.
		 * @param	tessEvalShader   	The tess eval shader.
		 * @param	fragShader		 	The fragment shader.
		 */
		virtual void Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& fragShader) = 0;

		/**
		 * @fn	virtual void IShader::Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& geoShader, const std::string& fragShader) = 0;
		 *
		 * @brief	Loads.
		 *
		 * @param	vertShader		 	The vertical shader.
		 * @param	tessControlShader	The tess control shader.
		 * @param	tessEvalShader   	The tess eval shader.
		 * @param	geoShader		 	The geo shader.
		 * @param	fragShader		 	The fragment shader.
		 */
		virtual void Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& geoShader, const std::string& fragShader) = 0;

		/**
		 * @fn	virtual void IShader::Define(const std::string& macro) = 0;
		 *
		 * @brief	Defines the given macro.
		 *
		 * @param	macro	The macro.
		 */
		virtual void Define(const std::string& macro) = 0;

		/**
		 * @fn	virtual void IShader::Define(const std::string& macro, const std::string& value) = 0;
		 *
		 * @brief	Defines.
		 *
		 * @param	macro	The macro.
		 * @param	value	The value.
		 */
		virtual void Define(const std::string& macro, const std::string& value) = 0;

		/**
		 * @fn	virtual void IShader::Compile() = 0;
		 *
		 * @brief	Compiles this object.
		 */
		virtual void Compile() = 0;

        /**
         * @fn	virtual void IShader::Use() = 0;
         *
         * @brief	Uses this object.
         */
        virtual void Use() = 0;

		virtual void AddUniform(const std::string& id) = 0;
		
		int GetUniform (const std::string& id) 
		{
			return m_uniforms[id];
		}
	protected:
		std::map<std::string, int> m_uniforms;
    };
}



