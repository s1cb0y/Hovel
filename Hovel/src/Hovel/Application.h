#pragma once
#include "Core.h"

#include "Window.h"
#include "Hovel/LayerStack.h"
#include "Hovel/Events/Event.h"
#include "Hovel/Events/ApplicationEvent.h"

#include "Hovel/ImGui/ImGuiLayer.h"
#include "Hovel/Core/TimeStep.h"

#include "Hovel/Renderer/Shader.h"
#include "Hovel/Renderer/Buffer.h"
#include "Hovel/Renderer/VertexArray.h"
#include "Hovel/Renderer/OrthoGraphCamera.h"

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
		bool OnWindowResize(WindowResizeEvent& e);
		bool SetCameraOrientation(KeyPressedEvent& e);
		bool m_Running = true;
		bool m_Minimized = false;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_layerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined by CLIENT
	Application* CreateApplication();
}
 
