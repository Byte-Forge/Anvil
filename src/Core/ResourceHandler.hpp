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
#include "../Graphics/Material.hpp"

namespace hpse
{
    class ResourceHandler
    {
    public:
		std::shared_ptr<ITexture> GetTextureArray(std::vector<std::string> names);
        std::shared_ptr<ITexture> GetTexture(const std::string &name);

		std::shared_ptr<Material> GetMaterial(const std::string &name);

		void AddResource(const std::string &name, std::shared_ptr<IResource> resource);

		inline void AddModDir(const std::string& dir)
		{
			if (std::find(m_modDirs.begin(), m_modDirs.end(), dir) != m_modDirs.end())
				return;

			m_modDirs.push_back(dir);
		}

    private:
		std::string m_texturesDir = "textures/";
		std::string m_shadersDir = "shader/";
		std::string m_materialsDir = "materials/";
		std::string m_w4dDir = "w4d/";
		std::string m_uiDir = "ui/";

        std::map<const std::string, std::shared_ptr<IResource>> m_resources;
		std::vector<std::string> m_modDirs;

		int GetFilePath(std::string name, std::string* path);
    };
}


