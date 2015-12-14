//
// Created by stephan on 14.12.15.
//

#pragma once
#include "../IRenderable.hpp"

namespace hpse
{
    namespace GL
    {
        class Terrain : public IRenderable
        {
        public:
            Terrain(std::uint32_t width, std::uint32_t height);

            void Render();
            void Update();
        private:

        };
    }
}




