#include "Application.h"
#include "Hovel/Events/ApplicationEvent.h"
#include "Hovel/Log.h"

namespace Hovel {
	
	Application::Application()	
	{
	}
	Application::~Application()	
	{
	}
	void Application::Run() {	
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
			HV_TRACE(e);
		if (e.IsInCategory(EventCategoryMouse))
			HV_TRACE(e);
		while (true);
	}	   	 
}