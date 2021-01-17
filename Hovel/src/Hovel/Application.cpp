#include "hvpch.h"
#include "Application.h"

#include "Hovel/Log.h"

#include "glad/glad.h"

#include "Input.h"

namespace Hovel {
	
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	
	Application::Application() 
	{
		HV_CORE_ASSERT(!s_Instance , "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};
		// Generate Vertex Buffer
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"} });
		
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Generate Index Buffer
		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		float verticesSquare[3 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 
			 0.5f, -0.5f, 0.0f, 
			 0.5f,  0.5f, 0.0f,
			 -0.5f, 0.5f, 0.0f
		};

		m_VertexArrayBlueSquare.reset(VertexArray::Create());
		vertexBuffer.reset(VertexBuffer::Create(verticesSquare, sizeof(verticesSquare)));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position"}	});

		m_VertexArrayBlueSquare->AddVertexBuffer(vertexBuffer);
		
		unsigned int indicesSquare[6] = { 0, 1, 2, 2, 3, 0};
		indexBuffer.reset(IndexBuffer::Create(indicesSquare, sizeof(indicesSquare) / sizeof(uint32_t)));
		m_VertexArrayBlueSquare->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		out vec3 v_Position;
		out vec4 v_Color;

		void main()
		{
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = vec4(a_Position, 1.0);
		}
		)";

		std::string fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;
		in vec3 v_Position;
		in vec4 v_Color;
		void main()
		{
			color = vec4(v_Position * 0.5 + 0.5, 1.0);
			color = v_Color;
		}
		)";
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		std::string vertexBlueSquareSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		out vec3 v_Position;

		void main()
		{
			v_Position = a_Position;
			gl_Position = vec4(a_Position, 1.0);
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
		m_ShaderBlueSquare.reset(new Shader(vertexBlueSquareSrc, fragmentBlueSquareSrc));

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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_ShaderBlueSquare->Bind();
			m_VertexArrayBlueSquare->Bind();

			glDrawElements(GL_TRIANGLES, m_VertexArrayBlueSquare->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();

			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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