#include "Core.hpp"
#include "Environment.hpp"

int main(int argc, char** argv) 
{
	Environment::Args = std::vector<std::string>(argv, argv + argc);
	hpse::Core engine;

	engine.Run();
	return 0;
}