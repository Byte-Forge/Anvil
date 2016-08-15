#include "Logger.hpp"
#include "../Core.hpp"
#include "../GUI.hpp"
using namespace anvil;

std::mutex Logger::s_mutex;

void Logger::Print(const std::string& msg,const Logger::Type type)
{
	std::string output = "";

	switch(type)
	{
		case LOG_INFO:
			output = "\\cy[INFO]: ";
			break;
		case LOG_WARNING:
			output = "\\co[WARNING]: ";
			break;
		case LOG_ERROR:
			output = "\\cr[ERROR]: ";
			break;
	}
	output+=msg;
	output+='\n';
	s_mutex.lock();
	Core::GetCore()->GetGUI()->AddTextToConsole(output);
	s_mutex.unlock();
}
