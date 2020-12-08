#pragma once
#include "Core.h"
#include "Events/Event.h"
namespace Hovel {
	class HOVEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};
	
	Application* CreateApplication();
}
 
