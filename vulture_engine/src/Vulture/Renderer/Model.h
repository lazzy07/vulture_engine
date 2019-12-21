#pragma once

#include "Mesh.h"

#include <vector>

namespace Vulture {
	class Model {
	public:
		Model();
		~Model();
		void AddMesh(Ref<Mesh> mesh);
	private:
		std::vector<Ref<Mesh>> m_Meshes;
	};
}
