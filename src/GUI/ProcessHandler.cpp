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
	return true;
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

    CefRefPtr<CefV8Value> func_close = CefV8Value::CreateFunction("close", handler);
    object->SetValue("close", func_close, V8_PROPERTY_ATTRIBUTE_NONE);

	int mapCount = 10;
	CefRefPtr<CefV8Value> map_list = CefV8Value::CreateArray(mapCount);
	for (int i = 0;i < mapCount;++i)
	{
		map_list->SetValue(i, CefV8Value::CreateString("map - " + std::to_string(i)));
	}
	object->SetValue("VAR_MAP_LIST", map_list, V8_PROPERTY_ATTRIBUTE_READONLY);
}