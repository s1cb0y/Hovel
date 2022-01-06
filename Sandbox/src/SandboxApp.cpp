#include <Hovel.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public Hovel::Layer
{
public:
	ExampleLayer()
		: Layer("Example") , m_CameraController(1280.0f / 720.0f, true)
	{


		// Generate Vertex Buffer
		Hovel::Ref<Hovel::VertexBuffer> vertexBuffer;
		Hovel::Ref<Hovel::IndexBuffer> indexBuffer;

		// Create 3D cube
		float cubeVertices[5 * 4] = {
			// positions         // texture coords
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left 
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // top left 
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // top right
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // bottom right 
		};

		uint32_t cubeIndices[] = {
			 0, 1, 2, 2, 3, 0
		};

		m_VACube.reset(Hovel::VertexArray::Create());

		vertexBuffer.reset(Hovel::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices)));
		vertexBuffer->SetLayout({ { Hovel::ShaderDataType::Float3, "a_Position" },
								  { Hovel::ShaderDataType::Float2, "a_TexCoord" } 
		});		
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

		m_ShaderSquare = Hovel::Shader::Create("BlueShader", vertexBlueSquareSrc, fragmentBlueSquareSrc);

 		Hovel::Ref<Hovel::Shader> textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Hovel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Hovel::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Hovel::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Hovel::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	~ExampleLayer()
	{
	}
	
	void OnUpdate(Hovel::TimeStep ts) override
	{		
		//HV_INFO("TimeStep {}s, {}ms", ts.GetSeconds(), ts.GetMilliseconds());
		
		m_CameraController.OnUpdate(ts);

		Hovel::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		Hovel::RenderCommand::Clear();

		Hovel::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1));
		
		

		std::dynamic_pointer_cast<Hovel::OpenGLShader>(m_ShaderSquare)->Bind();
		std::dynamic_pointer_cast<Hovel::OpenGLShader>(m_ShaderSquare)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Hovel::Renderer::Submit(m_VACube, m_ShaderSquare, transform);
			}
		}
				
		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind();
		Hovel::Renderer::Submit(m_VACube, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Hovel::Renderer::Submit(m_VACube, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		Hovel::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_SquareColor));
		ImGui::End();
	
	}
	void OnEvent(Hovel::Event& e) override
	{	
		m_CameraController.OnEvent(e);
	}

private:
	Hovel::ShaderLibrary m_ShaderLibrary;
	Hovel::Ref<Hovel::Shader> m_ShaderSquare;
	Hovel::Ref<Hovel::VertexArray> m_VACube;	
	Hovel::OrthographicCameraController m_CameraController;

	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f};
	Hovel::Ref<Hovel::Texture2D> m_Texture, m_ChernoLogoTexture;
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