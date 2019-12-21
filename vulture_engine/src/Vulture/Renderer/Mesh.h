#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "Vulture/Renderer/Buffer.h"
#include "Vulture/Renderer/VertexArray.h"
#include "Vulture/Renderer/Shader.h"

namespace Vulture {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct Texture {
		unsigned int id;
		std::string type;
	};

	class Mesh {
	public:
		void Draw(Ref<Shader> shader, glm::vec3 position, glm::vec3 rotation);
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		~Mesh() = default;
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<Texture> m_Textures;
	private:
		Ref<VertexBuffer> m_VBO;
		Ref<VertexArray> m_VAO;
		Ref<IndexBuffer> m_EBO;
	private:
		void SetupMesh();

		BufferLayout m_Layout = {
		{Vulture::ShaderDataType::Float3, "a_Position"},
		{Vulture::ShaderDataType::Float3, "a_Normal"},
		{Vulture::ShaderDataType::Float2, "a_TexCoord"}
		};
	};
}