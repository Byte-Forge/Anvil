//
// Created by stephan on 24.11.15.
//

#pragma once
#include <include/cef_app.h>

namespace hpse
{
    class ProcessHandler : public CefApp, public CefBrowserProcessHandler,
                            public CefRenderProcessHandler
    {
    public:
        ProcessHandler();
        ~ProcessHandler();

        virtual void OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info)
                OVERRIDE;
        virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
        virtual void OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) OVERRIDE;

        virtual bool OnProcessMessageReceived(
                CefRefPtr<CefBrowser> browser,
                CefProcessId source_process,
                CefRefPtr<CefProcessMessage> message) OVERRIDE;

        virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE;

        virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
                                      CefRefPtr<CefFrame> frame,
                                      CefRefPtr<CefV8Context> context) OVERRIDE;
    private:
        IMPLEMENT_REFCOUNTING(ProcessHandler);
    };
}



