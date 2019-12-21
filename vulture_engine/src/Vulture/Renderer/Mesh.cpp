#include "vulpch.h"
#include  "Mesh.h"
#include "Vulture/Renderer/Renderer.h"
#include <zip/zip.h>

namespace Vulture {
	void Mesh::Draw(Ref<Shader> shader, glm::vec3 position, glm::vec3 rotation)
	{
		Renderer::Submit(shader, m_VAO, position, rotation);
	}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) :
		m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
	{
		SetupMesh();
	}

	void Mesh::SetupMesh()
	{
		m_VAO.reset(VertexArray::Create());
		m_VBO.reset(VertexBuffer::Create((float *)&m_Vertices[0], sizeof(m_Vertices.size())));
		m_VBO->SetLayout(m_Layout);
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->SetIndexBuffer(m_EBO);
		
		m_EBO.reset(IndexBuffer::Create((uint32_t *)&m_Indices[0], m_Indices.size()));
	}
}