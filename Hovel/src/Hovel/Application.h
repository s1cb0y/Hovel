#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Hovel/Events/ApplicationEvent.h"

#include "Window.h"
namespace Hovel {
	class HOVEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();

		void OnEvent(Event &e);
	private:

		bool OnWindowClose(WindowCloseEvent& e);

		bool m_Running = true;
		std::unique_ptr<Window> m_window;
	};

	// To be defined by CLIENT
	Application* CreateApplication();
}
 
