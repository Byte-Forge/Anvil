/*
************************************
* Copyright (C) 2016 ByteForge
* SystemInterface.cpp
************************************
*/

#include <Rocket/Core.h>
#include "SystemInterface.hpp"
#include <iostream>
#define GLW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "../Exception.hpp"
#include "../Core.hpp"
using namespace anvil;


int SystemInterface::GetKeyModifiers(int mod)
{
	int km;
	if (mod&GLFW_MOD_SHIFT)
		km |= Rocket::Core::Input::KM_SHIFT;
	if(mod&GLFW_MOD_CONTROL)
		km |= Rocket::Core::Input::KM_CTRL;
	if(mod&GLFW_MOD_ALT)
		km |= Rocket::Core::Input::KM_ALT;
	
	return km;
}

Rocket::Core::Input::KeyIdentifier SystemInterface::TranslateKey(int Key)
{
	Rocket::Core::Input::KeyIdentifier ki;
	switch(Key)
	{
		case GLFW_KEY_UNKNOWN:	ki = Rocket::Core::Input::KI_UNKNOWN; break;
		case GLFW_KEY_SPACE:	ki = Rocket::Core::Input::KI_SPACE; break;
		case GLFW_KEY_COMMA:	ki = Rocket::Core::Input::KI_OEM_COMMA; break;
		case GLFW_KEY_MINUS:	ki = Rocket::Core::Input::KI_OEM_MINUS; break;
		case GLFW_KEY_PERIOD:	ki = Rocket::Core::Input::KI_OEM_PERIOD; break;
		case GLFW_KEY_0:		ki = Rocket::Core::Input::KI_0; break;
		case GLFW_KEY_1:		ki = Rocket::Core::Input::KI_1; break;
		case GLFW_KEY_2:		ki = Rocket::Core::Input::KI_2; break;
		case GLFW_KEY_3:		ki = Rocket::Core::Input::KI_3; break;
		case GLFW_KEY_4:		ki = Rocket::Core::Input::KI_4; break;
		case GLFW_KEY_5:		ki = Rocket::Core::Input::KI_5; break;
		case GLFW_KEY_6:		ki = Rocket::Core::Input::KI_6; break;
		case GLFW_KEY_7:		ki = Rocket::Core::Input::KI_7; break;
		case GLFW_KEY_8:		ki = Rocket::Core::Input::KI_8; break;
		case GLFW_KEY_9:		ki = Rocket::Core::Input::KI_9; break;
		case GLFW_KEY_A:		ki = Rocket::Core::Input::KI_A; break;
		case GLFW_KEY_B:		ki = Rocket::Core::Input::KI_B; break;
		case GLFW_KEY_C:		ki = Rocket::Core::Input::KI_C; break;
		case GLFW_KEY_D:		ki = Rocket::Core::Input::KI_D; break;
		case GLFW_KEY_E:		ki = Rocket::Core::Input::KI_E; break;
		case GLFW_KEY_F:		ki = Rocket::Core::Input::KI_F; break;
		case GLFW_KEY_G:		ki = Rocket::Core::Input::KI_G; break;
		case GLFW_KEY_H:		ki = Rocket::Core::Input::KI_H; break;
		case GLFW_KEY_I:		ki = Rocket::Core::Input::KI_I; break;
		case GLFW_KEY_J:		ki = Rocket::Core::Input::KI_J; break;
		case GLFW_KEY_K:		ki = Rocket::Core::Input::KI_K; break;
		case GLFW_KEY_L:		ki = Rocket::Core::Input::KI_L; break;
		case GLFW_KEY_M:		ki = Rocket::Core::Input::KI_M; break;
		case GLFW_KEY_N:		ki = Rocket::Core::Input::KI_N; break;
		case GLFW_KEY_O:		ki = Rocket::Core::Input::KI_O; break;
		case GLFW_KEY_P:		ki = Rocket::Core::Input::KI_P; break;
		case GLFW_KEY_Q:		ki = Rocket::Core::Input::KI_Q; break;
		case GLFW_KEY_R:		ki = Rocket::Core::Input::KI_R; break;
		case GLFW_KEY_S:		ki = Rocket::Core::Input::KI_S; break;
		case GLFW_KEY_T:		ki = Rocket::Core::Input::KI_T; break;
		case GLFW_KEY_U:		ki = Rocket::Core::Input::KI_U; break;
		case GLFW_KEY_V:		ki = Rocket::Core::Input::KI_V; break;
		case GLFW_KEY_W:		ki = Rocket::Core::Input::KI_W; break;
		case GLFW_KEY_X:		ki = Rocket::Core::Input::KI_X; break;
		case GLFW_KEY_Y:		ki = Rocket::Core::Input::KI_Y; break;
		case GLFW_KEY_Z:		ki = Rocket::Core::Input::KI_Z; break;
		case GLFW_KEY_F1:		ki = Rocket::Core::Input::KI_F1; break;
		case GLFW_KEY_F2:		ki = Rocket::Core::Input::KI_F2; break;
		case GLFW_KEY_F3:		ki = Rocket::Core::Input::KI_F3; break;
		case GLFW_KEY_F4:		ki = Rocket::Core::Input::KI_F4; break;
		case GLFW_KEY_F5:		ki = Rocket::Core::Input::KI_F5; break;
		case GLFW_KEY_F6:		ki = Rocket::Core::Input::KI_F6; break;
		case GLFW_KEY_F7:		ki = Rocket::Core::Input::KI_F7; break;
		case GLFW_KEY_F8:		ki = Rocket::Core::Input::KI_F8; break;
		case GLFW_KEY_F9:		ki = Rocket::Core::Input::KI_F9; break;
		case GLFW_KEY_F10:		ki = Rocket::Core::Input::KI_F10; break;
		case GLFW_KEY_F11:		ki = Rocket::Core::Input::KI_F11; break;
		case GLFW_KEY_F12:		ki = Rocket::Core::Input::KI_F12; break;
		case GLFW_KEY_ESCAPE:	ki = Rocket::Core::Input::KI_ESCAPE; break;
		default: ki = Rocket::Core::Input::KI_UNKNOWN; break;
	};

	return ki;
};

float SystemInterface::GetElapsedTime()
{
	return Core::GetCore()->GetTimer().GetElapsedTime() / 1e6;
};

bool SystemInterface::LogMessage(Rocket::Core::Log::Type type, const Rocket::Core::String& message)
{
	if (type == Rocket::Core::Log::LT_ERROR)
	{
		std::string msg = "LibRocket Error: " + std::string(message.CString());
		throw AnvilException(msg, __FILE__, __LINE__);
		return true;
	}
		
	return false;
};