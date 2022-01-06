#include "hvpch.h"
#include "Application.h"

#include "Hovel/Log.h"

#include "Hovel/Renderer/Renderer.h"

#include "Input.h"
#include "KeyCodes.h"

#include "GLFW/glfw3.h" // TODO only temporary till platform "TIME" class is implemented

namespace Hovel {
	
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	
	Application::Application()		 
	{
		HV_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}
	Application::~Application()	
	{
	}
		
	void Application::OnEvent(Event &e)
	{		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));		
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));		
		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	void Application::Run() {	
		
		HV_CORE_INFO("Run application");
		float lastTime = 0.0f;
		while (m_Running)
		{		
			float currentTime = (float) glfwGetTime(); //TODO Platform::GetTime()
			TimeStep timeStep = currentTime - lastTime;
			lastTime = currentTime;
			
			if (!m_Minimized)
			{
				for (Layer* layer : m_layerStack)
					layer->OnUpdate(timeStep);			
			}						

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		m_layerStack.PopLayer(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) 
	{
		if (e.GetHeight() == 0 || e.GetWidth() == 0)
		{
			m_Minimized = true;
		}
		else
		{
			m_Minimized = false;
			Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		}
		return false;
	}
}