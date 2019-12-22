#include "vulpch.h"
#include  "Mesh.h"
#include "Vulture/Renderer/Renderer.h"
#include <zip/zip.h>

namespace Vulture {
	VulMesh::VulMesh(void* vertices, size_t vSize, void* indices, size_t iSize) :
		m_Vertices((Vertex *)vertices), m_Indices((unsigned int *)indices), m_VerticesSize(vSize), m_IndicesSize(iSize)
	{
		SetupMesh();
	}

	VulMesh::VulMesh() {

	}

	VulMesh::~VulMesh() {
		VUL_CORE_TRACE("Mesh data deleted");
		free(m_Vertices);
		free(m_Indices);
	}

	void VulMesh::Draw(Ref<Shader> shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		Renderer::Submit(shader, m_VAO, position, rotation, scale);
	}

	void VulMesh::SetupMesh()
	{
		m_VAO.reset(VertexArray::Create());
		m_VBO.reset(VertexBuffer::Create((float *)m_Vertices, m_VerticesSize));
		m_IBO.reset(IndexBuffer::Create(m_Indices, m_IndicesSize/sizeof(unsigned int)));

		m_VBO->SetLayout(m_Layout);
		m_VAO->AddVertexBuffer(m_VBO);
		m_VAO->SetIndexBuffer(m_IBO);
	}
}