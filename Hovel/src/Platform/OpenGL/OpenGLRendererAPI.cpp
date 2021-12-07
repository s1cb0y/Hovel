#include "hvpch.h"

#include "OpenGLRendererAPI.h"

#include "glad/glad.h"
namespace Hovel {

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);		
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4 & color)
	{		
		glClearColor(color.r, color.b, color.g, color.a);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}