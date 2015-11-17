#pragma once
#include <string>

namespace hpse
{
    class IResource
    {
		virtual void Load(const std::string& file) {};

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