//
// Created by stephan on 24.11.15.
//

#include "JsHandler.hpp"
#include "../Core.hpp"
#include <iostream>

using namespace hpse;

//Add a handler for each native function that should be available in JS here
bool JsHandler::Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments,
                        CefRefPtr<CefV8Value> &retval, CefString &exception)
{
	std::cout << "works" << std::endl;
    if(name=="quit")
    {
		std::cout << "test" << std::endl;
        Core::Quit();
    }

    return false;
}
