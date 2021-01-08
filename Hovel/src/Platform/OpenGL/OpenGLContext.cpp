#include "hvpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"

namespace Hovel{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle (windowHandle)
	{
		HV_ASSERT(windowHandle, "Window handle is null");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		// Init glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HV_ASSERT(status, "Failed to init Glad!");

		HV_CORE_INFO("VERSION: {0}", glGetString(GL_VERSION));
		HV_CORE_INFO("VENDOR: {0}", glGetString(GL_VENDOR));
		HV_CORE_INFO("RENDERER: {0}", glGetString(GL_RENDERER));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}