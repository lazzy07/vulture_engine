#pragma once
#include "Material.h"

namespace Vulture {
	class MaterialLibrary {
	public:
		MaterialLibrary(Ref<ShaderLibrary> shaderLibrary, Ref<TextureLibrary> textureLibrary);
		~MaterialLibrary();
		
		void Load(std::string name);
		void RemoveMaterial(std::string name);

		Ref<Material> AddNewMaterial(std::string name, std::string shaderName="default");
		Ref<Material> GetMaterial(const std::string name);

		bool Exists(const std::string name);

		inline std::unordered_map<std::string, Ref<Material>>* GetAll() { return &m_Materials; }

		std::string MaterialsToConfigBuffer();
	private:
		std::unordered_map<std::string, Ref<Material>> m_Materials;
		Ref<ShaderLibrary> m_ShaderLibrary;
		Ref<TextureLibrary> m_TextureLibrary;
	};
}
