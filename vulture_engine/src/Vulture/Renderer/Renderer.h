#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "Vulture/Core/DispatchQueue.h"
#include "Vulture/Core/Window.h"

namespace Vulture {
	class Renderer {
	public:
		static void Init(Ref<Window> window);

		static void BeginScene(Ref<Camera> camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scaling = glm::vec3(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static Ref<Window> m_Window;
		static SceneData* m_SceneData;
		static DispatchQueue* m_RendererQueue;
	};
}