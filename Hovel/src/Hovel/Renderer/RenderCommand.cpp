#include "hvpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hovel {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}