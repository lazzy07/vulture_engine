#pragma once
#include "Material.h"

namespace Vulture {
	class MaterialLibrary {
	public:
		MaterialLibrary();
		~MaterialLibrary();
		
		void Load(std::string name, Ref<Material> material);
		void RemoveMaterial(std::string name);

		Ref<Material> GetMaterial(const std::string name);
		bool Exists(const std::string name);

		std::string MaterialToConfigBuffer();
	private:
		std::unordered_map<std::string, Ref<Material>> m_Materials;
	};
}
