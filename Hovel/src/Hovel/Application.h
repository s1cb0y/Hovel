#pragma once
#include "Core.h"
#include "Hovel/Events/Event.h"
#include "Hovel/Events/ApplicationEvent.h"
#include "Hovel/LayerStack.h"
#include "Window.h"

namespace Hovel {
	class HOVEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
		void OnEvent(Event &e);
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

	private:

		bool OnWindowClose(WindowCloseEvent& e);

		bool m_Running = true;
		std::unique_ptr<Window> m_window;
		LayerStack m_layerStack;
	};

	// To be defined by CLIENT
	Application* CreateApplication();
}
 
