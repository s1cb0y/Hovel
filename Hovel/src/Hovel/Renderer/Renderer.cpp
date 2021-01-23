#include "hvpch.h"
#include "Renderer.h"


namespace Hovel{

	glm::mat4* Renderer::s_ViewProjMatrix = new glm::mat4;

	void Renderer::BeginScene(OrthoGraphCamera& camera)
	{
		*s_ViewProjMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->UploadUniform("u_ViewProjection", *s_ViewProjMatrix);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}