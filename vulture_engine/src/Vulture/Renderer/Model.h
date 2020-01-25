#pragma once

#include "Mesh.h"

#include <vector>
#include "Vulture/Core/Configurations.h"
#include "Vulture/Renderer/Material.h"

namespace Vulture {
	class Model {
	public:
		Model(std::string name);
		~Model();
		void AddMesh(std::string name, Ref<VulMesh> mesh);
		inline const Configurations GetConfigurations() const { return m_Config; };
		void Draw(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		void SetConfigurations(char* conf);
		inline void SetName(std::string name) { m_Name = name; };
		inline int GetMeshCount() { return m_Meshes.size(); };
		void SetMaterial(std::string meshName);

		void ChangeMaterial(std::string meshName, std::string materialName);

		void SaveConfig();

		inline std::string GetName() const { return m_Name; };
		inline std::unordered_map<std::string, Ref<VulMesh>>* GetMeshes() { return &m_Meshes; };
		inline std::unordered_map<std::string, Ref<Material>>* GetMaterials() { return &m_Materials; };
	private:
		std::unordered_map<std::string, Ref<VulMesh>> m_Meshes;
		std::unordered_map<std::string, Ref<Material>> m_Materials;
		Configurations m_Config;
		std::string m_Name;
	};
}
