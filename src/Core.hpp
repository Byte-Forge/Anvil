#pragma once
#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include "Graphics.hpp"
#include "Script.hpp"
#include "GUI.hpp"
#include "Audio.hpp"
#include "Types/Map.hpp"
#include "Core/ResourceHandler.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Frustum.hpp"

namespace hpse
{
	class Core
	{
	public: 
		Core();
		~Core();

		void Run();

		inline std::unique_ptr<GUI>& GetGUI()
		{
			return m_gui;
		}

		inline std::unique_ptr<Script>& GetScript()
		{
			return m_script;
		}

		inline std::unique_ptr<Graphics>& GetGraphics()
		{
			return m_graphics;
		}

		inline std::unique_ptr<ResourceHandler>& GetResources()
		{
			return m_resources;
		}

		inline std::unique_ptr<Map>& GetMap()
		{
			return m_map;
		}

		inline std::unique_ptr<Camera>& GetCamera()
		{
			return m_camera;
		} 

		inline glm::vec2 GetResolution()
		{
			glm::vec2 res;
			res.x = (float)m_window.getSize().x;
			res.y = (float)m_window.getSize().y;
			return res;
		}

		inline void Quit()
		{
			m_running = false;
		}

		static inline Core* GetCore()
		{
			return m_instance;
		}
	private:
		sf::Window m_window;
		std::unique_ptr<ResourceHandler> m_resources;
		std::unique_ptr<Graphics> m_graphics;
		std::unique_ptr<GUI> m_gui;
		std::unique_ptr<Script> m_script;
		std::unique_ptr<Audio> m_audio;
		std::unique_ptr<Map> m_map;
		std::unique_ptr<Camera> m_camera;
		std::unique_ptr<Frustum> m_frustum;
		bool m_running;
		static Core* m_instance;
	};
}