#pragma once

#ifdef HV_PLATFORM_WINDOWS

extern Hovel::Application* Hovel::CreateApplication();

int main(int argc, char ** argv) {
	Hovel::Log::Init();
	HV_CORE_INFO("Logging initialized!");
	auto app = Hovel::CreateApplication();
	app->Run();
	delete app;
}
#else
	#error Hovel only supports windows!
#endif 
