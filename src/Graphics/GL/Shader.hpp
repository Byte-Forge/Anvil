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

            void Load(const std::string& vertShader, const std::string& fragShader);
            void Load(const std::string& vertShader, const std::string& geoShader, const std::string& fragShader);
            void Compile();
            void Use();
			inline std::uint32_t GetID()
			{
				return (std::uint32_t)m_program;
			}
        private:
            void LoadShader(const std::string file,GLenum type);
            GLuint m_program;
            std::map<GLenum,GLuint> m_shaders;
        };
    }
}