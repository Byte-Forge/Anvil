#include "MethodHandler.hpp"
#include <Awesomium/JSValue.h>
#include <Awesomium/STLHelpers.h>
using namespace hpse;
using namespace Awesomium;

MethodHandler::MethodHandler(unsigned int my_remote) : m_remote_id(my_remote)
{

}

void MethodHandler::OnMethodCall(WebView * caller, unsigned int remote_object_id, const WebString & method_name, const JSArray & args)
{
	if (remote_object_id == m_remote_id)
	{
		if (method_name == WSLit("quit"))
		{

		}
	}
}

JSValue MethodHandler::OnMethodCallWithReturnValue(WebView * caller, unsigned int remote_object_id, const WebString & method_name, const JSArray & args)
{
	if (remote_object_id == m_remote_id)
	{

	}

	return JSValue::Undefined();
}
