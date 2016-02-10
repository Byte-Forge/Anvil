/*
************************************
* Copyright (C) 2016 ByteForge
* SystemInterface.hpp
************************************
*/

#pragma once
#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/Input.h>
#include <SFML/Window.hpp>

namespace anvil
{
	class SystemInterface : public Rocket::Core::SystemInterface
	{
	public:

		Rocket::Core::Input::KeyIdentifier TranslateKey(sf::Keyboard::Key Key);
		int GetKeyModifiers(sf::Window *Window);
		float GetElapsedTime();
		bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);

	private:
		sf::Clock m_timer;
	};
}