#pragma once
#include "RenderCommand.h"

#include "OrthoGraphCamera.h"
#include "Shader.h"

namespace Hovel {
		
	class Renderer
	{
	public:
		static void BeginScene(OrthoGraphCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }			
	private:
		static glm::mat4* s_ViewProjMatrix;
	};

}