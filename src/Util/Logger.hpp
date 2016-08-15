#pragma once
#include <string>
#include <mutex>

namespace anvil
{
	class Logger
	{
	public:
		enum Type
		{
			LOG_INFO	= 0,
			LOG_WARNING = 1,
			LOG_ERROR	= 2
		};

		static void Print(const std::string& msg, const Type = LOG_INFO);
	private:
		static std::mutex s_mutex;
	};
}