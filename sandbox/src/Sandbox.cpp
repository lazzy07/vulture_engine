#include "Vulture.h"

class Sandbox : public Vulture::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Vulture::Application* Vulture::CreateApplication() {
	return new Sandbox();
}