#include "hvpch.h"
#include "Application.h"

#include "Hovel/Events/ApplicationEvent.h"
#include "Hovel/Log.h"

#include<GLFW/glfw3.h>

namespace Hovel {
	
	Application::Application()	
	{
		m_window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application()	
	{
	}
	void Application::Run() {	
		
		HV_CORE_INFO("Run application");
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}
	}	   	 
}