#include "vulpch.h"
#include "MaterialLibrary.h"
#include "zip/zip.h"
#include "Vulture/Core/FileManager.h"
namespace Vulture {
	MaterialLibrary::MaterialLibrary(Ref<ShaderLibrary> shaderLibrary, Ref<TextureLibrary> textureLibrary) : 
		m_ShaderLibrary(shaderLibrary), m_TextureLibrary(textureLibrary)
	{
	}

	MaterialLibrary::~MaterialLibrary()
	{
	}

	void MaterialLibrary::Load(std::string name)
	{
		if (name != "default") {
			VUL_CORE_ASSERT(!Exists(name), "Material with same name already exists");
		}
		
		std::string fileName = "./assets/materials/" + name + ".vulmat";
		
		Ref<Material> m;
		Configurations cfg;
		struct zip_t *zip = zip_open(fileName.c_str(), 0, 'r');
		char *buf;

		{
			zip_entry_open(zip, "material");
			{
				size_t bufsize;
				bufsize = zip_entry_size(zip);
				buf = (char *)malloc(bufsize);
				zip_entry_noallocread(zip, (void *)buf, bufsize);
			}
			zip_entry_close(zip);
		}
		zip_close(zip);

		cfg.LoadConfigBuffer(buf);

		m.reset(new Material(name, cfg.GetString("shader", "name", "default"), m_ShaderLibrary, m_TextureLibrary));
		m->SetConfigurations(cfg.GetConfigBuffer());
		m->LoadVariables();
		free(buf);
		m_Materials[name] = m;
	}

	void MaterialLibrary::RemoveMaterial(std::string name)
	{
		m_Config.RemoveEntry("materials", name);
		m_Materials.erase(name);
	}

	Ref<Material> MaterialLibrary::AddNewMaterial(std::string name, std::string shaderName)
	{
		if (name != "default") {
			VUL_CORE_ASSERT(!Exists(name), "Material with same name already exists");
		}
		Ref<Material> newMaterial;
		newMaterial.reset(new Material(name, shaderName, m_ShaderLibrary, m_TextureLibrary));
		m_Config.SetString("materials", name, name);
		m_Materials[name] = newMaterial;
		return newMaterial;
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
		//std::string materialChar = "";
		//for (std::pair<std::string, Ref<Material>> elem : m_Materials) {
		//	materialChar.append(elem.second->GetConfigurations().GetConfigBuffer());
		//}
		//return materialChar;
		return m_Config.GetConfigBuffer();
	}
}