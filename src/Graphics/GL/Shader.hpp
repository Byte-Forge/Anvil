//
// Created by stephan on 28.10.15.
//

#pragma once
#include "../IShader.hpp"
#include "flextGL.h"
#include <map>
#include <GL/gl.h>

namespace hpse
{
    namespace GL
    {
        class Shader : public IShader
        {
        public:
            Shader();
            ~Shader();

			void Define(const std::string& macro);
			void Define(const std::string& macro, const std::string& value);
            void Load(const std::string& vertShader, const std::string& fragShader);
            void Load(const std::string& vertShader, const std::string& geoShader, const std::string& fragShader);
			void Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& fragShader);
			void Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& geoShader, const std::string& fragShader);
            void Compile();
            void Use();
			inline GLuint GetUniformLocation(const std::string& id)
			{
				return glGetUniformLocation(m_program, id.c_str());
			}
        private:
            void LoadShader(const std::string& file,GLenum type);
            GLuint m_program;
            std::map<GLenum,GLuint> m_shaders;
			std::map<std::string,std::string> m_macros;
			static const std::string glslVersion;
        };
    }
}