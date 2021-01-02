#include "hvpch.h"
#include "WindowsWindow.h"

#include "Hovel/Events/MouseEvent.h"
#include "Hovel/Events/KeyEvent.h"
#include "Hovel/Events/ApplicationEvent.h"

#include "glad/glad.h"

namespace Hovel
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int errorcode, const char* msg)
	{
		HV_CORE_ERROR("GLFW Error ({0}) : {1}", errorcode, msg);
	}
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
	WindowsWindow::WindowsWindow(const WindowProps &props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProps &props)
	{
		m_Data.Title	= props.Title;
		m_Data.Height	= props.Height;
		m_Data.Width	= props.Width;

		HV_CORE_INFO("Creating window {0} ({1} {2})", props.Title, props.Width, props.Height);
		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HV_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		// Init glad
		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		HV_ASSERT(status, "Failed to init Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
	
		SetVSync(true);
		
		// Set glfw callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
			HV_CORE_ASSERT((data != nullptr), "Could not get user pointer!");			
			data->Height = height;
			data->Width = width;
			WindowResizeEvent event(width, height);						
			data->EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
			HV_CORE_ASSERT((data != nullptr), "Could not get user pointer!");
			WindowCloseEvent event;
			data->EventCallback(event);
		});
				
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data->EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data->EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data->EventCallback(event);
					break;
				}
			}

		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data->EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}