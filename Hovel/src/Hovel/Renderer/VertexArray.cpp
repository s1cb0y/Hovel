#include "hvpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Hovel {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HV_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		HV_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}