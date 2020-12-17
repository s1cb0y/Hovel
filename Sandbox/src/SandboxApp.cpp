#include <Hovel.h>

class ExampleLayer : public Hovel::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	~ExampleLayer()
	{
	}
	void OnUpdate() override
	{
		HV_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hovel::Event& e) override
	{	
		HV_TRACE("ExampleLayer, {0}", e.GetName());
	}
};

class Sandbox : public Hovel::Application {
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
		
};

Hovel::Application* Hovel::CreateApplication() {
	return new Sandbox();
}