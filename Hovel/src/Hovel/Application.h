#pragma once
#include "Core.h"

#include "Window.h"
#include "Hovel/LayerStack.h"
#include "Hovel/Events/Event.h"
#include "Hovel/Events/ApplicationEvent.h"

#include "Hovel/ImGui/ImGuiLayer.h"

#include "Hovel/Renderer/Shader.h"
#include "Hovel/Renderer/Buffer.h"

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
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_layerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};

	// To be defined by CLIENT
	Application* CreateApplication();
}
 
