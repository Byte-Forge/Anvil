//
// Created by stephan on 24.11.15.
//

#include "ProcessHandler.hpp"
#include "JsHandler.hpp"
#include <iostream>
using namespace hpse;

ProcessHandler::ProcessHandler()
{

}

ProcessHandler::~ProcessHandler()
{

}

void ProcessHandler::OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info)
{
    std::cout << "INFO: Created Cef Renderer!" << std::endl;
}

void ProcessHandler::OnBrowserCreated(CefRefPtr<CefBrowser> browser)
{
    std::cout << "INFO: Created Cef Browser!" << std::endl;
}

void ProcessHandler::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)
{
    std::cout << "INFO: Shutdown Cef Browser!" << std::endl;
}

bool ProcessHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process,
                                              CefRefPtr<CefProcessMessage> message)
{
	return false;
}

CefRefPtr<CefRenderProcessHandler> ProcessHandler::GetRenderProcessHandler()
{
    return this;
}

void ProcessHandler::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                                      CefRefPtr<CefV8Context> context)
{
    CefRefPtr<CefV8Value> object = context->GetGlobal();
    CefRefPtr<CefV8Handler> handler = new JsHandler(browser);

    CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("quit", handler);
    object->SetValue("quit", func, V8_PROPERTY_ATTRIBUTE_NONE);
}