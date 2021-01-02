#pragma once
#include "Core.h"

#include "Window.h"
#include "Hovel/LayerStack.h"
#include "Hovel/Events/Event.h"
#include "Hovel/Events/ApplicationEvent.h"

namespace Hovel {
	class HOVEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
		void OnEvent(Event &e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance;}
	private:

		bool OnWindowClose(WindowCloseEvent& e);

		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		LayerStack m_layerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined by CLIENT
	Application* CreateApplication();
}
 
