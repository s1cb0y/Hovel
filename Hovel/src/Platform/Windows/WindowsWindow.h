#pragma once
#include "Hovel/Window.h"
#include "Hovel/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Hovel 
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline void* GetNativeWindow() const { return m_Window; };

	private:
		void Init(const WindowProps &props);
		void ShutDown();
	private:

		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		unsigned int m_Width;
		unsigned int m_Height;

		struct WindowData
		{
			std::string Title;
			unsigned int Height;
			unsigned int Width;
			bool VSync;
			EventCallbackFn EventCallback;
		};
			
		WindowData m_Data;
	};
}