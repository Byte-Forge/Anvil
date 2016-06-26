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

		/**
		 * @fn	virtual void IShader::GetUniform(const std::string& id) = 0;
		 *
		 * @brief	Get handle to an uniform in shader.
		 *
		 * @param	id	The identifier.
		 * 				
		 * @return	The handle to the uniform.
		 */
		virtual int GetUniform(const std::string& id) = 0;


		virtual int GetUniformBuffer(const std::string& id, int index) = 0;
	protected:
		std::map<std::string, int> m_uniforms;
		std::map<std::string, int> m_ubos;
    };
}



