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
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

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
			 * @fn	void Shader::Define(const std::string& macro);
			 *
			 * @brief	Defines the given macro.
			 *
			 * @param	macro	The macro.
			 */
			void Define(const std::string& macro);

			/**
			 * @fn	void Shader::Define(const std::string& macro, const std::string& value);
			 *
			 * @brief	Defines.
			 *
			 * @param	macro	The macro.
			 * @param	value	The value.
			 */
			void Define(const std::string& macro, const std::string& value);

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
			 * @fn	void Shader::AddUniform(const std::string& name);
			 *
			 * @brief	Adds an uniform.
			 *
			 * @param	name	The name.
			 */
			void AddUniform(const std::string& name);
			
        private:
            void LoadShader(const std::string& file,GLenum type);

		private:
            GLuint m_program;
            std::map<GLenum,GLuint> m_shaders;
			std::map<std::string,std::string> m_macros;
			static const std::string glslVersion;
        };
    }
}