#include "vulpch.h"
#include "MaterialLibrary.h"
#include "zip/zip.h"

namespace Vulture {
	MaterialLibrary::MaterialLibrary()
	{
	}

	MaterialLibrary::~MaterialLibrary()
	{
	}

	void MaterialLibrary::Load(std::string name, Ref<ShaderLibrary> shaderLibrary)
	{
		VUL_CORE_ASSERT(!Exists(name), "Material with same name already exists");
		Ref<Material> m;

		std::string fileName = "./assets/materials/" + name + ".vulmat";
		Configurations cfg;
		struct zip_t *zip = zip_open(fileName.c_str(), 0, 'r');
		char *buf;

		{
			zip_entry_open(zip, "material");
			{
				size_t bufsize;
				buf = (char *)malloc(bufsize);
			}
			zip_entry_close(zip);
		}
		zip_close(zip);

		cfg.LoadConfigBuffer(buf);

		m.reset(new Material(name, cfg.GetString("shader", "name"), shaderLibrary));

		free(buf);
		m_Materials[name] = m;
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

	std::string MaterialLibrary::MaterialsToConfigBuffer()
	{
		std::string materialChar = "";
		for (std::pair<std::string, Ref<Material>> elem : m_Materials) {
			materialChar.append(elem.second->GetConfigurations().GetConfigBuffer());
		}
		return materialChar;
	}
}