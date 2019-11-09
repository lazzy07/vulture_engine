#include "Vulture.h"

class ExampleLayer : public Vulture::Layer {
public:
	ExampleLayer(): Layer("Example") {

	}

	void OnUpdate() override {
		//VUL_INFO("ExampleLayer::update");

		if (Vulture::Input::IsKeyPressed(VUL_KEY_TAB))
			VUL_INFO("Tab key pressed down");
	}

	void OnEvent(Vulture::Event& event) override {
		//VUL_TRACE("{0}", event);
	}

};

class Sandbox : public Vulture::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Vulture::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Vulture::Application* Vulture::CreateApplication() {
	return new Sandbox();
}