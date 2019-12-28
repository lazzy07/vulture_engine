#include "vulpch.h"
#include "MaterialLibrary.h"

namespace Vulture {
	MaterialLibrary::MaterialLibrary()
	{
	}

	MaterialLibrary::~MaterialLibrary()
	{
	}

	void MaterialLibrary::AddMaterial(std::string name, Ref<Material> material)
	{
		VUL_CORE_ASSERT(!Exists(name), "Material with same name already exists");
		m_Materials[name] = material;
	}

	void MaterialLibrary::RemoveMaterial(std::string name)
	{
		m_Materials.erase(name);
	}

	Ref<Material> MaterialLibrary::GetMaterial(const std::string name)
	{
		VUL_CORE_ASSERT(Exists(name), "Material does not exists");
		return m_Materials[name];
	}

	bool MaterialLibrary::Exists(const std::string name)
	{
		return m_Materials.find(name) != m_Materials.end();
	}

	void MaterialLibrary::LoadMaterialsFromConfig(std::string path)
	{

	}

	std::string MaterialLibrary::MaterialToConfigBuffer()
	{
		std::string materialChar = "";
		for (std::pair<std::string, Ref<Material>> elem : m_Materials) {
			materialChar.append(elem.second->GetConfigurations().GetConfigBuffer());
		}
		return materialChar;
	}
}