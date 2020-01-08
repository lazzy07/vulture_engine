#include "vulpch.h"
#include "Material.h"

namespace Vulture {
	Material::Material(const std::string name, const std::string shaderName, Ref<ShaderLibrary> shaderLibrary) 
		: m_Name(name), m_Shaders(shaderLibrary) {
		m_Configurations.SetString("material", "name", name);
		m_Configurations.SetString("shader", "name", shaderName);
	}

	Material::~Material() {

	}

	Ref<Shader> Material::GetShader()
	{
		return m_Shaders->Get(m_Configurations.GetString("shader", "name", "default"));
	}

	void Material::SetShader(std::string shaderName)
	{
		m_Configurations.SetString("shader", "name", shaderName);
	}
}