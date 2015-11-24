//
// Created by stephan on 24.11.15.
//

#pragma once
#include <include/cef_v8.h>
namespace hpse
{
    class JsHandler : public CefV8Handler
    {
    public:
        virtual bool Execute(const CefString& name,
                             CefRefPtr<CefV8Value> object,
                             const CefV8ValueList& arguments,
                             CefRefPtr<CefV8Value>& retval,
                             CefString& exception) OVERRIDE;
    private:
        IMPLEMENT_REFCOUNTING(JsHandler);
    };
}



