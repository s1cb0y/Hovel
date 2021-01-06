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
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}