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
}