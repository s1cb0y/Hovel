#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
namespace Hovel {
	class HOVEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	private:
		bool m_Running = true;
		std::unique_ptr<Window> m_window;
	};

	// To be defined by CLIENT
	Application* CreateApplication();
}
 
