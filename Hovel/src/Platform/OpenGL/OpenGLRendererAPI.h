#pragma once
#include "Hovel/Renderer/RendererAPI.h"

namespace Hovel {
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void Init() override;
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override ;
	};
}