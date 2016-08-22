#include "ScriptEngine.hpp"
#include "../Core.hpp"
#include "../Script.hpp"
using namespace anvil;

ScriptEngine::ScriptEngine() : IScriptEngine("lua")
{

}

void ScriptEngine::ExecuteString(const std::string& script)
{
    Core::GetCore()->GetScript()->RunString(script);
}

void ScriptEngine::ExecuteFile(const std::string& file)
{
	 Core::GetCore()->GetScript()->LoadFile(file);
}