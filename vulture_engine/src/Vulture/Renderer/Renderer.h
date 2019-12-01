#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "Vulture/Core/DispatchQueue.h"

namespace Vulture {
	class Renderer {
	public:
		static void Init();

		static void BeginScene(Ref<Camera> camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
		static DispatchQueue* m_RendererQueue;
	};
}