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

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }			
	private:
		static glm::mat4* s_ViewProjMatrix;
	};

}