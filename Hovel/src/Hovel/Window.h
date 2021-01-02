#pragma once
#include "hvpch.h"

#include "Hovel/Core.h"
#include "Hovel/Events/Event.h"

namespace Hovel
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Height;
		unsigned int Width;

		WindowProps(const std::string& title = "Hovel Engine", 
					unsigned int w = 1280, 
					unsigned int h = 720)
			: Height{h}, Width{w}, Title{title}
		{
		}
	};
	// interface representing a desktop system based window
	class HOVEL_API Window
	{
	public:

		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}
