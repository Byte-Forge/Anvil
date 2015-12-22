#pragma once
#include <Awesomium/JSObject.h>

namespace hpse
{
	class MethodHandler : public Awesomium::JSMethodHandler
	{
	public:
		MethodHandler(unsigned int my_remote);

		void OnMethodCall(Awesomium::WebView* caller,
			unsigned int remote_object_id,
			const Awesomium::WebString& method_name,
			const Awesomium::JSArray& args);

		Awesomium::JSValue OnMethodCallWithReturnValue(Awesomium::WebView* caller,
			unsigned int remote_object_id,
			const Awesomium::WebString& method_name,
			const Awesomium::JSArray& args);
	private:
		unsigned int m_remote_id;
	};
}
