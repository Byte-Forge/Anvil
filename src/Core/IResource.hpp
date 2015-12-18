#pragma once
#include <string>

namespace hpse
{
    class IResource
    {
	public:
		virtual ~IResource() {};
        inline bool KeepLoaded()
        {
            return m_keepLoaded;
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