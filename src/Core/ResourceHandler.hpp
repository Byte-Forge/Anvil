//
// Created by stephan on 11.11.15.
//
#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>
#include "IResource.hpp"
#include "../Graphics/ITexture.hpp"

namespace hpse
{
    class ResourceHandler
    {
    public:

        std::shared_ptr<ITexture> GetTexture(const std::string& name);
		void AddResource(const std::string &name, std::shared_ptr<IResource> resource);

		inline void AddMapDir(const std::string& dir)
		{
			m_mapDirs.push_back(dir);
		}

		inline void AddModelDir(const std::string& dir)
		{
			m_modelDirs.push_back(dir);
		}

		inline void AddTexDir(const std::string& dir)
		{
			m_texDirs.push_back(dir);
		}

    private:
        std::map<const std::string, std::shared_ptr<IResource>> m_resources;
		std::vector<std::string> m_mapDirs;
		std::vector<std::string> m_texDirs;
		std::vector<std::string> m_modelDirs;

    };
}


