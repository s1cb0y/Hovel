#include <Hovel.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		uint32_t cubeIndices[] = {
			 0, 1, 2, 2, 3, 0
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
		uniform mat4 u_Transform;

		out vec3 v_Position;

		void main()
		{
			v_Position = a_Position;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
		)";

		std::string fragmentBlueSquareSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 color;
		in vec3 v_Position;
		uniform vec3 u_Color;
		void main()
		{
			color = vec4(u_Color, 1.0);
		}
		)";
		m_ShaderSquare.reset(Hovel::Shader::Create(vertexBlueSquareSrc, fragmentBlueSquareSrc));

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

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1));
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		

		std::dynamic_pointer_cast<Hovel::OpenGLShader>(m_ShaderSquare)->Bind();
		std::dynamic_pointer_cast<Hovel::OpenGLShader>(m_ShaderSquare)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int i = 0; i < 5; i++)
		{
			position.x += 0.11;
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;			
			Hovel::Renderer::Submit(m_VACube, m_ShaderSquare, transform);
		}

		Hovel::Renderer::EndScene();
	}

	void OnImGuiRender()
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
		ImGui::End();
	
	}
	void OnEvent(Hovel::Event& e) override
	{	
	}

private:
	std::shared_ptr<Hovel::Shader> m_ShaderSquare;
	std::shared_ptr<Hovel::VertexArray> m_VACube;
	Hovel::OrthoGraphCamera m_Camera;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotation = 0.0f;
	const float m_CameraSpeed = 1.00f;
	const float m_RotationSpeed = 15.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f};
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