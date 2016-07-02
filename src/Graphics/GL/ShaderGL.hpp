/*
************************************
* Copyright (C) 2016 ByteForge
* Shader.hpp
************************************
*/

#pragma once
#include "../IShader.hpp"
#include "flextGL.h"
#include <map>

namespace anvil
{
    namespace GL
    {
        /**
         * @class	Shader
         *
         * @brief	A shader.
         */
        class Shader : public IShader
        {
        public:

            /**
             * @fn	Shader::Shader();
             *
             * @brief	Default constructor.
             */
            Shader();

            /**
             * @fn	Shader::~Shader();
             *
             * @brief	Destructor.
             */
            ~Shader();

            /**
             * @fn	void Shader::Load(const std::string& vertShader, const std::string& fragShader);
             *
             * @brief	Loads.
             *
             * @param	vertShader	The vertical shader.
             * @param	fragShader	The fragment shader.
             */
            void Load(const std::string& vertShader, const std::string& fragShader);

            /**
             * @fn	void Shader::Load(const std::string& vertShader, const std::string& geoShader, const std::string& fragShader);
             *
             * @brief	Loads.
             *
             * @param	vertShader	The vertical shader.
             * @param	geoShader 	The geo shader.
             * @param	fragShader	The fragment shader.
             */
            void Load(const std::string& vertShader, const std::string& geoShader, const std::string& fragShader);

			/**
			 * @fn	void Shader::Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& fragShader);
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
			 * @fn	void Shader::Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& geoShader, const std::string& fragShader);
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

			/**
			 * @fn	void Shader::Compile();
			 *
			 * @brief	Compiles this object.
			 */
			void Compile();

            /**
             * @fn	void Shader::Use();
             *
             * @brief	Uses this object.
             */
            void Use();

			/**
			* @fn	int ShaderGL::GetUniform(const std::string& id);
			*
			* @brief	Get handle to an uniform in shader.
			*
			* @param	id	The identifier.
			*
			* @return	The handle to the uniform.
			*/
			int GetUniform(const std::string& id);

            int GetUniformBuffer(const std::string& id);

			void AttachUBO(const std::string& name, int id);

		private:
            GLuint m_program;
            std::map<GLenum,GLuint> m_shaders;

		private:
			void LoadShader(const std::string& file, GLenum type);
        };
    }
}