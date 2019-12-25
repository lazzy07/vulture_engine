#include "vulpch.h"
#include "Model.h"

namespace Vulture {
	Model::Model(std::string name) : m_Name(name) {
		
	}

	Model::~Model() {

	}

	void Model::AddMesh(std::string name, Ref<VulMesh> mesh)
	{
		m_Meshes[name] = mesh;
	}

	void Model::Draw(Ref<Shader> shader)
	{
		for (std::pair<std::string, Ref<VulMesh>> mesh : m_Meshes) {
			mesh.second->Draw(shader, m_Position, m_Roation, m_Scale);
		}
	}

	void Model::SetConfigurations(char* conf)
	{
		m_Config.LoadConfigBuffer(conf);

		m_Position = {
			m_Config.GetFloat(m_Name, "posX", 0.0f),
			m_Config.GetFloat(m_Name, "posY", 0.0f),
			m_Config.GetFloat(m_Name, "posZ", 0.0f)
		};

		m_Roation = {
			m_Config.GetFloat(m_Name, "rotX", 0.0f),
			m_Config.GetFloat(m_Name, "rotY", 0.0f),
			m_Config.GetFloat(m_Name, "rotZ", 0.0f),
		};

		m_Scale = {
			m_Config.GetFloat(m_Name, "scaleX", 0.0f),
			m_Config.GetFloat(m_Name, "scaleY", 0.0f),
			m_Config.GetFloat(m_Name, "scaleZ", 0.0f),
		};
	}
}