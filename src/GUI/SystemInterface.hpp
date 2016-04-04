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
	/**
	 * @class	SystemInterface
	 *
	 * @brief	A system interface.
	 */
	class SystemInterface : public Rocket::Core::SystemInterface
	{
	public:

		/**
		 * @fn	int SystemInterface::GetKeyModifiers(int mod);
		 *
		 * @brief	Gets key modifiers.
		 *
		 * @param	mod	The modifier.
		 *
		 * @return	The key modifiers.
		 */
		int GetKeyModifiers(int mod);

		/**
		 * @fn	Rocket::Core::Input::KeyIdentifier SystemInterface::TranslateKey(int key);
		 *
		 * @brief	Translate key.
		 *
		 * @param	key	The key.
		 *
		 * @return	A Rocket::Core::Input::KeyIdentifier.
		 */
		Rocket::Core::Input::KeyIdentifier TranslateKey(int key);

		/**
		 * @fn	float SystemInterface::GetElapsedTime();
		 *
		 * @brief	Gets elapsed time.
		 *
		 * @return	The elapsed time.
		 */
		float GetElapsedTime();

		/**
		 * @fn	bool SystemInterface::LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);
		 *
		 * @brief	Logs a message.
		 *
		 * @param	type   	The type.
		 * @param	message	The message.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		bool LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message);
	};
}