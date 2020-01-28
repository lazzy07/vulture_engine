#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Vulture/Renderer/Buffer.h"
#include "Vulture/Renderer/VertexArray.h"
#include "Vulture/Renderer/Shader.h"

namespace Vulture {
	struct Vertex;

	//struct Texture;

	class VulMesh {
	public:
		VulMesh(void* vertices, size_t vSize, void* indices, size_t iSize);
		VulMesh();
		~VulMesh();

		inline const BufferLayout getLayout() const { return m_Layout; };
		
		void Draw(Ref<Shader> shader, glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec3 rotation = { 0.0f, 0.0f, 0.0f }, glm::vec3 scale = { 1.0f, 1.0f, 1.0f });
		void SetupMesh();

	public:
		Vertex* m_Vertices;
		uint32_t m_VerticesSize;
		unsigned int* m_Indices;
		uint32_t m_IndicesSize;
	private:
		Ref<VertexBuffer> m_VBO;
		Ref<VertexArray> m_VAO;
		Ref<IndexBuffer> m_IBO;

		BufferLayout m_Layout = {
			{Vulture::ShaderDataType::Float3, "a_Position"},
			{Vulture::ShaderDataType::Float3, "a_Normal"},
			{Vulture::ShaderDataType::Float2, "a_TexCoord"}
		};
	};
}