#include "hvpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace Hovel {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: HV_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
		}

		HV_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HV_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		HV_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}