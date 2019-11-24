#include "Vulture.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Vulture/Renderer/ShaderLibrary.h"

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


		vertexBuff->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuff);



		uint32_t indecies[6] = { 0, 1, 2, 2, 3, 0 };
		Vulture::Ref<Vulture::IndexBuffer> indexBuff;
		indexBuff.reset(Vulture::IndexBuffer::Create(indecies, sizeof(indecies)));
		m_VertexArray->SetIndexBuffer(indexBuff);

		auto exampleShader = m_ShaderLibrary.Load("./assets/shaders/texture.glsl");
		m_Texture = Vulture::Texture2D::Create("./assets/textures/logo_only.png");

		std::dynamic_pointer_cast<Vulture::OpenGLShader>(exampleShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Vulture::Timestep timestep) override {

		m_Controller->RunController();

		Vulture::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Vulture::RenderCommand::Clear();

		Vulture::Renderer::BeginScene(m_Controller->GetCamera());
		m_Texture->Bind();
		Vulture::Renderer::Submit(m_ShaderLibrary.Get("texture"), m_VertexArray, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
		Vulture::Renderer::Submit(m_ShaderLibrary.Get("texture"), m_VertexArray, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
		Vulture::Renderer::Submit(m_ShaderLibrary.Get("texture"), m_VertexArray, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
		Vulture::Renderer::Submit(m_ShaderLibrary.Get("texture"), m_VertexArray, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f });
		Vulture::Renderer::Submit(m_ShaderLibrary.Get("texture"), m_VertexArray, { 0.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
		Vulture::Renderer::Submit(m_ShaderLibrary.Get("texture"), m_VertexArray, { 0.0f, 0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f });
		Vulture::Renderer::Submit(m_ShaderLibrary.Get("texture"), m_VertexArray, { 0.0f, 0.0f, 0.5f }, { 0.0f, 0.0f, 0.0f });
		Vulture::Renderer::Submit(m_ShaderLibrary.Get("texture"), m_VertexArray, { 0.3f, 0.3f, 0.3f }, { 0.0f, 0.0f, 0.0f });
		Vulture::Renderer::Submit(m_ShaderLibrary.Get("texture"), m_VertexArray, { 1.0f, 1.0f, 1.0f }, {0.0f, 0.0f, 0.0f });
		Vulture::Renderer::EndScene();
	}

	void OnEvent(Vulture::Event& event) override {
		
	}
private:
	Vulture::ShaderLibrary m_ShaderLibrary;
	Vulture::Ref<Vulture::VertexArray> m_VertexArray;
	Vulture::Ref<Vulture::Texture2D> m_Texture;

	Vulture::Ref<Vulture::FirstPersonController> m_Controller;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 1.0f;
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