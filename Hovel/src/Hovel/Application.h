#pragma once
#include "Core.h"

namespace Hovel {
	class HV_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};
	
	Application* CreateApplication();
}
 
