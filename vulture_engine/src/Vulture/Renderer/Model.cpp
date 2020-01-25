#include "vulpch.h"
#include "Model.h"
#include "Vulture/Core/Application.h"
#include "zip/zip.h"

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
				m_Materials[ele.first]->Bind();
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

	void Model::ChangeMaterial(std::string meshName, std::string materialName)
	{
		m_Config.SetString(meshName, "material", materialName);
		m_Materials[meshName] = Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(materialName);
	}

	void Model::SaveConfig()
	{
		std::string configBuffer = m_Config.GetConfigBuffer();

		std::string path = "./assets/models/" + m_Name + ".vulmodel";

		struct zip_t *zip = zip_open(path.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'a');
		{
			zip_entry_open(zip, "ConfigFile.vulconf");
			{
				zip_entry_write(zip, configBuffer.c_str(), strlen(configBuffer.c_str()));
			}
			zip_entry_close(zip);
		}
		zip_close(zip);
	}
}