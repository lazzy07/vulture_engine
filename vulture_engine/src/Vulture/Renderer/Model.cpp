#include "vulpch.h"
#include "Model.h"
#include "Vulture/Core/Application.h"

namespace Vulture {
	Model::Model(std::string name) : m_Name(name) {
		
	}

	Model::~Model() {

	}

	void Model::AddMesh(std::string name, Ref<VulMesh> mesh)
	{
		m_Meshes[name] = mesh;
	}

	void Model::Draw(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		for (std::pair<std::string, Ref<VulMesh>> ele : m_Meshes) {
			//VUL_CORE_ASSERT(m_Materials[ele.first], "Cannot find assigned material for the mesh");
			if (m_Materials[ele.first]) {
				ele.second->Draw(m_Materials[ele.first]->GetShader(), position, rotation, scale);
			}
		}
	}

	void Model::SetConfigurations(char* conf)
	{
		m_Config.LoadConfigBuffer(conf);
		Ref<MaterialLibrary> ml = Application::Get().GetCurrentLevel()->GetMaterialLibrary();

		for (std::pair<std::string, Ref<VulMesh>> ele : m_Meshes) {
			std::string matName = m_Config.GetString(ele.first, "material", "");
			VUL_CORE_TRACE("Material slot for {0} is : {1}", ele.first, matName);
			SetMaterial(ele.first);
			VUL_CORE_ASSERT(ml->Exists(matName), "Cannot find the material");
		}
	}

	void Model::SetMaterial(std::string meshName)
	{
		std::string materialName = m_Config.GetString(meshName, "material", "");
		m_Materials[meshName] = Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(materialName);
	}
}