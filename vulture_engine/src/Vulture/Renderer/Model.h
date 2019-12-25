#pragma once

#include "Mesh.h"

#include <vector>
#include "Vulture/Core/Configurations.h"

namespace Vulture {
	class Model {
	public:
		Model(std::string name);
		~Model();
		void AddMesh(std::string name, Ref<VulMesh> mesh);
		inline const Configurations GetConfigurations() const { return m_Config; };
		void Draw(Ref<Shader> shader);
		void SetConfigurations(char* conf);
		inline void SetName(std::string name) { m_Name = name; }
	private:
		std::unordered_map<std::string, Ref<VulMesh>> m_Meshes;
		Configurations m_Config;
		std::string m_Name;

		glm::vec3 m_Position;
		glm::vec3 m_Roation;
		glm::vec3 m_Scale;
	};
}
