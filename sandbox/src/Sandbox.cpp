#include "Vulture.h"
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Vulture::Layer {
public:
	ExampleLayer(): Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
		m_VertexArray.reset(Vulture::VertexArray::Create());

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

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;			
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main(){
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragSrc = R"(
			#version 330 core			
			layout(location = 0) out vec4 color;
			
			in vec2 v_TexCoord;
			uniform sampler2D u_Texture;

			void main(){
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_Shader.reset(Vulture::Shader::Create(vertexSrc, fragSrc));
		m_Texture = Vulture::Texture2D::Create("./assets/textures/logo_only.png");

		std::dynamic_pointer_cast<Vulture::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Vulture::Timestep timestep) override {
		
		if (Vulture::Input::IsKeyPressed(VUL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * timestep;
		else if (Vulture::Input::IsKeyPressed(VUL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * timestep;
		
		if (Vulture::Input::IsKeyPressed(VUL_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * timestep;
		else if (Vulture::Input::IsKeyPressed(VUL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * timestep;

		Vulture::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Vulture::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(0.0f);

		Vulture::Renderer::BeginScene(m_Camera);
		m_Texture->Bind();
		Vulture::Renderer::Submit(m_Shader, m_VertexArray, { 0.0f, 0.0f, 0.0f }, {0.0f, 0.0f, 0.0f });
		Vulture::Renderer::EndScene();
	}

	void OnEvent(Vulture::Event& event) override {
		
	}
private:
	Vulture::Ref<Vulture::Shader> m_Shader;
	Vulture::Ref<Vulture::VertexArray> m_VertexArray;
	Vulture::Ref<Vulture::Texture2D> m_Texture;

	Vulture::OrthographicCamera m_Camera;
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