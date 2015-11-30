#pragma once
#include <SFML/Window.hpp>
#include "Graphics.hpp"
#include "Script.hpp"
#include "GUI.hpp"
#include "Audio.hpp"
#include "Core/ResourceHandler.hpp"

namespace hpse
{
	class Core
	{
	public: 
		Core();
		~Core();

		void Run();

		static inline std::unique_ptr<GUI>& GetGUI()
		{
			return m_gui;
		}

		static inline std::unique_ptr<Script>& GetScript()
		{
			return m_script;
		}

		static inline std::unique_ptr<Graphics>& GetGraphics()
		{
			return m_graphics;
		}

		static inline std::unique_ptr<ResourceHandler>& GetResources()
		{
			return m_resources;
		}

		static inline void Quit()
		{
			m_running = false;
		}
	private:
		sf::Window m_window;
		static std::unique_ptr<ResourceHandler> m_resources;
		static std::unique_ptr<Graphics> m_graphics;
		static std::unique_ptr<GUI> m_gui;
		static std::unique_ptr<Script> m_script;
		static std::unique_ptr<Audio> m_audio;
		static bool m_running;
	};
}