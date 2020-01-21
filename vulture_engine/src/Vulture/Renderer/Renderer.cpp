#include "vulpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Vulture/Core/TaskManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


namespace Vulture {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	Ref<Window> Renderer::m_Window = nullptr;

	void Renderer::Init(Ref<Window> window)
	{
		m_Window = window;
		RenderCommand::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(Ref<Camera> camera)
	{
		m_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scaling)
	{
		GLFWwindow* window = (GLFWwindow*)m_Window->GetNativeWindow();
		glfwMakeContextCurrent(window);
		shader->Bind();
		//TODO:: Temparory
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotate = glm::rotate(translate, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		rotate = glm::rotate(rotate, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rotate = glm::rotate(rotate, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scale = glm::scale(rotate, scaling);

		//TODO:: Temparory
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", scale);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}