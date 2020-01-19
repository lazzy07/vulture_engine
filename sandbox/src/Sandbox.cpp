#include "Vulture.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Vulture/Renderer/ShaderLibrary.h"
#include "Vulture/Renderer/Mesh.h"

class ExampleLayer : public Vulture::Layer {
public:
	ExampleLayer() : Layer("Example") {
		m_VertexArray.reset(Vulture::VertexArray::Create());
		m_Controller.reset(new Vulture::FirstPersonController());
		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		Vulture::Ref<Vulture::VertexBuffer> vertexBuff;
		vertexBuff.reset(Vulture::VertexBuffer::Create(vertices, sizeof(vertices)));

		Vulture::BufferLayout layout = {
			{Vulture::ShaderDataType::Float3, "a_Position"},
			{Vulture::ShaderDataType::Float2, "a_TexCoord"}
		};

		Vulture::Ref<Vulture::Shader> m_exampleShader = m_ShaderLibrary.Load("./assets/shaders/texture.glsl");
		Vulture::Ref<Vulture::Shader> m_WhiteShader = m_ShaderLibrary.Load("./assets/shaders/white.glsl");

		m_Texture = Vulture::Texture2D::Create("./assets/textures/logo_only.png");

		std::dynamic_pointer_cast<Vulture::OpenGLShader>(m_exampleShader)->UploadUniformInt("u_Texture", 0);

		Vulture::ModelLoader::AddNewModel("./assets/fbx/door_01.fbx");
		Vulture::ModelLoader::LoadVulModel("./assets/models/door_01.vulmodel", &m_ModelLibrary);
		m_Model = m_ModelLibrary.GetModel("door_01");

		vertexBuff->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuff);

		uint32_t indecies[6] = { 0, 1, 2, 2, 3, 0 };
		Vulture::Ref<Vulture::IndexBuffer> indexBuff;
		indexBuff.reset(Vulture::IndexBuffer::Create(indecies, 6));
		m_VertexArray->SetIndexBuffer(indexBuff);
	}

	void OnUpdate(Vulture::Timestep timestep) override {

		m_Controller->RunController(VUL_KEY_W, VUL_KEY_S, VUL_KEY_A, VUL_KEY_D);

		Vulture::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Vulture::RenderCommand::Clear();

		Vulture::Renderer::BeginScene(m_Controller->GetCamera());
		m_Model->Draw(glm::vec3(0.0), glm::vec3(0.0), glm::vec3(1.0));
		m_Texture->Bind();
		Vulture::Renderer::Submit(m_ShaderLibrary.Get("texture"), m_VertexArray, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, glm::vec3(1.0f));
		
		Vulture::Renderer::EndScene();
	}

	void OnEvent(Vulture::Event& event) override {
		
	}
private:
	Vulture::ShaderLibrary m_ShaderLibrary;
	Vulture::ModelLibrary m_ModelLibrary;
	Vulture::Ref<Vulture::VertexArray> m_VertexArray;
	Vulture::Ref<Vulture::Texture2D> m_Texture;
	Vulture::Ref<Vulture::FirstPersonController> m_Controller;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 1.0f;

	Vulture::Ref<Vulture::Model> m_Model;
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