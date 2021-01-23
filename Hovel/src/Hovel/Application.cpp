#include "hvpch.h"
#include "Application.h"

#include "Hovel/Log.h"

#include "Hovel/Renderer/Renderer.h"

#include "Input.h"

namespace Hovel {
	
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	
	Application::Application()
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		HV_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	
		// Generate Vertex Buffer
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;
		
		// Create 3D cube

		float cubeVertices[] = {
		  -0.5f,0.5f,0.0f,
		  -0.5f,-0.5f,0.0f,
		  0.5f,0.5f,0.0f,
		  0.5f,-0.5f,0.0f,
		  -0.5f,0.5f,-0.5f,
		  -0.5f,-0.5f,-0.5f,
		  0.5f,0.5f,-0.5f,
		  0.5f,-0.5f,-0.5f
		};

		uint32_t cubeIndices[] = {
			  0, 2, 3, 1,
			  2, 6, 7, 3,
			  6, 4, 5, 7,
			  4, 0, 1, 5,
			  0, 4, 6, 2,
			  1, 5, 7, 3
		};

		m_VACube.reset(VertexArray::Create()); 
		
		vertexBuffer.reset(VertexBuffer::Create(cubeVertices, sizeof(cubeVertices)));
		vertexBuffer->SetLayout({ { ShaderDataType::Float3, "a_Position" } });
		m_VACube->AddVertexBuffer(vertexBuffer);
		indexBuffer.reset(IndexBuffer::Create(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t)));
		m_VACube->SetIndexBuffer(indexBuffer);

				
		std::string vertexBlueSquareSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		uniform mat4 u_ViewProjection;
		out vec3 v_Position;

		void main()
		{
			v_Position = a_Position;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
		}
		)";

		std::string fragmentBlueSquareSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;
		in vec3 v_Position;
		void main()
		{
			color = vec4(0.2, 0.2, 0.8, 1.0);
		}
		)";
		m_ShaderCube.reset(new Shader(vertexBlueSquareSrc, fragmentBlueSquareSrc));

	}
	Application::~Application()	
	{
	}

	void Application::OnEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	void Application::Run() {	
		
		HV_CORE_INFO("Run application");
		while (m_Running)
		{
			RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
			RenderCommand::Clear();
			
			m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
			m_Camera.SetRotation(45.0f);
			Renderer::BeginScene(m_Camera);
						
			Renderer::Submit(m_VACube, m_ShaderCube);
			
			Renderer::EndScene();
			
			for (Layer* layer : m_layerStack)
				layer->OnUpdate();
			
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
}