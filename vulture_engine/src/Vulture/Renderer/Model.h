#pragma once

#include "Mesh.h"

#include <vector>

namespace Vulture {
	class Model {
	public:
		Model();
		~Model();
		void AddMesh(Ref<Mesh> mesh);
		void Draw(Ref<Shader> s, glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
	private:
		std::vector<Ref<Mesh>> m_Meshes;
	};
}
