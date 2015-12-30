//
// Created by stephan on 11.11.15.
//
#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include "IResource.hpp"
#include "../Graphics/ITexture.hpp"

namespace hpse
{
    class ResourceHandler
    {
    public:
		std::shared_ptr<ITexture> GetTextureArray(std::vector<std::string> names);
        std::shared_ptr<ITexture> GetTexture(const std::string& name);
		void AddResource(const std::string &name, std::shared_ptr<IResource> resource);

		inline void AddMapDir(const std::string& dir)
		{
			if (std::find(m_mapDirs.begin(), m_mapDirs.end(), dir) != m_mapDirs.end())
				return;

			m_mapDirs.push_back(dir);
		}

		inline void AddModelDir(const std::string& dir)
		{
			if (std::find(m_modelDirs.begin(), m_modelDirs.end(), dir) != m_modelDirs.end())
				return;

			m_modelDirs.push_back(dir);
		}

		inline void AddTexDir(const std::string& dir)
		{
			if (std::find(m_texDirs.begin(), m_texDirs.end(), dir) != m_texDirs.end())
				return;
			m_texDirs.push_back(dir);
		}


		inline const std::vector<std::string>& GetMapDirs()
		{
			return m_mapDirs;
		}

		inline const std::vector<std::string>& GetModelDirs()
		{
			return m_modelDirs;
		}

		inline const std::vector<std::string>& GetTextureDirs()
		{
			return m_texDirs;
		}
    private:
        std::map<const std::string, std::shared_ptr<IResource>> m_resources;
		std::vector<std::string> m_mapDirs;
		std::vector<std::string> m_texDirs;
		std::vector<std::string> m_modelDirs;

    };
}


