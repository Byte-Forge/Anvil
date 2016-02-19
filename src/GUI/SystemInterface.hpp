/*
************************************
* Copyright (C) 2016 ByteForge
* SystemInterface.hpp
************************************
*/

#pragma once
#include <Rocket/Core/SystemInterface.h>
#include <Rocket/Core/Input.h>
#include <GLFW/glfw3.h>

namespace anvil
{
	class SystemInterface : public Rocket::Core::SystemInterface
	{
	public:
		int GetKeyModifiers(int mod);
		Rocket::Core::Input::KeyIdentifier TranslateKey(int key);
		float GetElapsedTime();
		bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);

	private:
	};
}