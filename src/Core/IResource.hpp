/*
************************************
* Copyright (C) 2016 ByteForge
* IResource.hpp
************************************
*/

#pragma once
#include <string>

namespace anvil
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