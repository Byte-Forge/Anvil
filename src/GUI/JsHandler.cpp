//
// Created by stephan on 24.11.15.
//

#include "JsHandler.hpp"
#include "../Core.hpp"
#include <iostream>

using namespace hpse;

JsHandler::JsHandler(CefRefPtr<CefBrowser> browser) : m_browser(browser)
{

}

//Add a handler for each native function that should be available in JS here
bool JsHandler::Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments,
                        CefRefPtr<CefV8Value> &retval, CefString &exception)
{

    if(name=="close")
    {
        CefRefPtr<CefProcessMessage> msg= CefProcessMessage::Create("close");
        m_browser->SendProcessMessage(PID_BROWSER,msg);
    }

    return false;
}
