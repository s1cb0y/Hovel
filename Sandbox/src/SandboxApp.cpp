#include <Hovel.h>

#include "imgui/imgui.h"

class ExampleLayer : public Hovel::Layer
{
public:
	ExampleLayer()
		: Layer("Example") , m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{


		// Generate Vertex Buffer
		std::shared_ptr<Hovel::VertexBuffer> vertexBuffer;
		std::shared_ptr<Hovel::IndexBuffer> indexBuffer;

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

		m_VACube.reset(Hovel::VertexArray::Create());

		vertexBuffer.reset(Hovel::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices)));
		vertexBuffer->SetLayout({ { Hovel::ShaderDataType::Float3, "a_Position" } });
		m_VACube->AddVertexBuffer(vertexBuffer);
		indexBuffer.reset(Hovel::IndexBuffer::Create(cubeIndices, sizeof(cubeIndices) / sizeof(uint32_t)));
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
		m_ShaderCube.reset(new Hovel::Shader(vertexBlueSquareSrc, fragmentBlueSquareSrc));

	}

	~ExampleLayer()
	{
	}
	
	void OnUpdate(Hovel::TimeStep ts) override
	{		
		HV_INFO("TimeStep {}s, {}ms", ts.GetSeconds(), ts.GetMilliseconds());
		if (Hovel::Input::IsKeyPressed(HV_KEY_LEFT))
			m_CameraPosition.x += m_CameraSpeed * ts;		
		else if (Hovel::Input::IsKeyPressed(HV_KEY_RIGHT))
			m_CameraPosition.x -= m_CameraSpeed * ts;
		if (Hovel::Input::IsKeyPressed(HV_KEY_UP))
			m_CameraPosition.y -= m_CameraSpeed * ts;
		else if (Hovel::Input::IsKeyPressed(HV_KEY_DOWN))
			m_CameraPosition.y += m_CameraSpeed * ts;
		m_Camera.SetPosition(m_CameraPosition);
		if (Hovel::Input::IsKeyPressed(HV_KEY_A))
			m_CameraRotation += m_RotationSpeed * ts;
		else if (Hovel::Input::IsKeyPressed(HV_KEY_D))
			m_CameraRotation -= m_RotationSpeed * ts;
		
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hovel::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Hovel::RenderCommand::Clear();

		Hovel::Renderer::BeginScene(m_Camera);

		Hovel::Renderer::Submit(m_VACube, m_ShaderCube);

		Hovel::Renderer::EndScene();
	}

	void OnImGuiRender()
	{
	
	}
	void OnEvent(Hovel::Event& e) override
	{	
	}

private:
	std::shared_ptr<Hovel::Shader> m_ShaderCube;
	std::shared_ptr<Hovel::VertexArray> m_VACube;
	Hovel::OrthoGraphCamera m_Camera;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotation = 0.0f;
	const float m_CameraSpeed = 1.00f;
	const float m_RotationSpeed = 15.0f;
};

class Sandbox : public Hovel::Application {
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
		
};

Hovel::Application* Hovel::CreateApplication() {
	return new Sandbox();
}