#include "Vulture.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Vulture/Renderer/ShaderLibrary.h"
#include "Vulture/Renderer/Mesh.h"

class ExampleLayer : public Vulture::Layer {
public:
	ExampleLayer() : Layer("Example") {
		m_Controller.reset(new Vulture::FirstPersonController());
		
		//std::dynamic_pointer_cast<Vulture::OpenGLShader>(m_exampleShader)->UploadUniformInt("u_Texture", 0);

		//m_Level->AddNewModel("./assets/fbx/door_01.fbx");
		//m_Level->AddModelToLevel("door_01", glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
		//m_Level->AddModelToLevel("door_01", glm::vec3(5.0f), glm::vec3(0.0f), glm::vec3(1.0f));
		//m_Level->SaveLevel();
		Vulture::Window& w = Vulture::Application::Get().GetWindow();
		
		m_Controller->GetCamera()->UpdateViewMatrix(w.GetHeight(), w.GetWidth());
	}

	void OnUpdate(Vulture::Timestep timestep) override {
		m_Level = Vulture::Application::Get().GetCurrentLevel();
		m_Controller->RunController(VUL_KEY_W, VUL_KEY_S, VUL_KEY_A, VUL_KEY_D);

		Vulture::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Vulture::RenderCommand::Clear();

		m_Level->Render(m_Controller->GetCamera());
	}

	void OnEvent(Vulture::Event& event) override {
		if (event.GetEventType() == Vulture::EventType::WindowResize) {
			Vulture::WindowResizeEvent& e = (Vulture::WindowResizeEvent&)event;
			m_Controller->GetCamera()->UpdateViewMatrix(e.GetHeight(), e.GetWidth(), 54.0f, 0.1f, 100.0f);
		}
	}
private:
	Vulture::Ref<Vulture::Level> m_Level = Vulture::Application::Get().GetCurrentLevel();
	Vulture::Ref<Vulture::FirstPersonController> m_Controller;

};

class Sandbox : public Vulture::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Vulture::Application* Vulture::CreateApplication() {
	return new Sandbox();
}