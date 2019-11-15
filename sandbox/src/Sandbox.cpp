#include "Vulture.h"

class ExampleLayer : public Vulture::Layer {
public:
	ExampleLayer(): Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
		m_VertexArray.reset(Vulture::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		std::shared_ptr<Vulture::VertexBuffer> vertexBuff;
		vertexBuff.reset(Vulture::VertexBuffer::Create(vertices, sizeof(vertices)));

		Vulture::BufferLayout layout = {
			{Vulture::ShaderDataType::Float3, "a_Position"},
			{Vulture::ShaderDataType::Float4, "a_Color"}
		};


		vertexBuff->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuff);



		uint32_t indecies[3] = { 0, 1, 2 };
		std::shared_ptr<Vulture::IndexBuffer> indexBuff;
		indexBuff.reset(Vulture::IndexBuffer::Create(indecies, 3));
		m_VertexArray->SetIndexBuffer(indexBuff);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;			
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;	

			void main(){
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragSrc = R"(
			#version 330 core			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main(){
				color = v_Color;
			}
		)";

		m_Shader.reset(new Vulture::Shader(vertexSrc, fragSrc));
	}

	void OnUpdate() override {
		Vulture::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Vulture::RenderCommand::Clear();

		m_Camera.SetPosition({ 0.5f, 0.5f, 0.5f });
		m_Camera.SetRotation(45.0f);

		Vulture::Renderer::BeginScene(m_Camera);
		Vulture::Renderer::Submit(m_Shader, m_VertexArray);
		Vulture::Renderer::EndScene();
	}

	void OnEvent(Vulture::Event& event) override {
		
	}
private:
	std::shared_ptr<Vulture::Shader> m_Shader;
	std::shared_ptr<Vulture::VertexArray> m_VertexArray;

	Vulture::OrthographicCamera m_Camera;
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