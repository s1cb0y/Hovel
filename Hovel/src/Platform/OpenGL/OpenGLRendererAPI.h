#pragma once
#include "Hovel/Renderer/RendererAPI.h"

namespace Hovel {
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override ;
	};
}