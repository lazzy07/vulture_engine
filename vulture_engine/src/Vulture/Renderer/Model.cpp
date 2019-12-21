#include "vulpch.h"
#include "Model.h"

namespace Vulture {
	Model::Model() {
		
	}

	Model::~Model() {

	}

	void Model::AddMesh(Ref<Mesh> mesh)
	{
		m_Meshes.push_back(mesh);
	}
	void Model::Draw(Ref<Shader> s, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		for (Ref<Mesh> mesh : m_Meshes) {
			mesh->Draw(s);
		}
	}
}