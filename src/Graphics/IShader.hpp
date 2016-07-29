/*
************************************
* Copyright (C) 2016 ByteForge
* IShader.hpp
************************************
*/

#pragma once
#include <string>
#include <map>
#include <vector>

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
		enum ShaderType
		{
			ANVIL_VERT_SHADER = 0,
			ANVIL_TESC_SHADER = 1,
			ANVIL_TESE_SHADER = 2,
			ANVIL_GEOM_SHADER = 3,
			ANVIL_FRAG_SHADER = 4,
		};

		IShader();

        /**
         * @fn	virtual void IShader::Load(const std::string& vertShader, const std::string& fragShader) = 0;
         *
         * @brief	Loads.
         *
         * @param	vertShader	The vertical shader.
         * @param	fragShader	The fragment shader.
         */
        void Load(const std::string& vertShader, const std::string& fragShader);

        /**
         * @fn	virtual void IShader::Load(const std::string& vertShader, const std::string& geoShader, const std::string& fragShader) = 0;
         *
         * @brief	Loads.
         *
         * @param	vertShader	The vertical shader.
         * @param	geoShader 	The geo shader.
         * @param	fragShader	The fragment shader.
         */
        void Load(const std::string& vertShader, const std::string& geoShader, const std::string& fragShader);

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
		void Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& fragShader);

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
		void Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& geoShader, const std::string& fragShader);


		virtual void LoadShader(const std::string& file, const ShaderType type);

		/**
		 * @fn	virtual void IShader::Link() = 0;
		 *
		 * @brief	Links this object.
		 */
		virtual void Link() = 0;

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

		virtual int GetUniformBuffer(const std::string& id) = 0;

		virtual void AttachUBO(const std::string& name, int id) = 0;

		void Update();

	protected:
		void Ready();

	protected:
		bool m_tracked;
		bool m_shouldReload = false;
		std::map<std::string, ShaderType> m_files;
		std::map<std::string, int> m_uniforms;
		std::map<std::string, int> m_ubos;
		std::map<std::string, int> m_ubo_indices;
    };
}



