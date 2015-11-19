#pragma once
#include <string>

namespace hpse
{
    class IResource
    {
        inline bool KeepLoaded()
        {
            return m_instanceable;
        }

        inline bool IsInstanceable()
        {
           return m_instanceable;
        }
    protected:
        bool m_keepLoaded;
        bool m_instanceable;
    };
}