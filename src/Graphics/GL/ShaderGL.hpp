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
			 * @fn	void Shader::Link();
			 *
			 * @brief	Links this object.
			 */
			void Link();

            /**
             * @fn	void Shader::Use();
             *
             * @brief	Uses this object.
             */
            void Use();

			virtual void LoadShader(const std::string& file, const ShaderType type);

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
            std::map<GLenum, GLuint> m_shaders;
			static std::map<ShaderType, GLenum> s_mapping;

        };
    }
}