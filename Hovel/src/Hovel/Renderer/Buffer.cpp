#include "hvpch.h"
#include "Buffer.h"

#include "Hovel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Hovel{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: HV_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		HV_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: HV_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		HV_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}