#pragma once
#include <Rocket/Core/EventListener.h>

namespace hpse
{
	class EventListener : public Rocket::Core::EventListener
	{
		void ProcessEvent(Rocket::Core::Event& event);
	};
}