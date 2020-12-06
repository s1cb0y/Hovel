#include <Hovel.h>

class Sandbox : public Hovel::Application {
public:
	Sandbox() {
	}

	~Sandbox() {
	}
};

Hovel::Application* Hovel::CreateApplication() {
	return new Sandbox();
}