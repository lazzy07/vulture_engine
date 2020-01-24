#pragma once
#include "Texture.h"
#include "Vulture/Core/Configurations.h"

namespace Vulture{
	class TextureLibrary {
	public:
		void Load(std::string path);
		Ref<Texture2D> GetTexture(std::string name);
		void RemoveTexture(std::string name);
		bool Exists(std::string name);

		std::string TexturesToConfigBuffer();

		inline std::unordered_map<std::string, Ref<Texture2D>>* GetAll() { return &m_Textures; };
	private:
		std::string GetFileName(std::string path);
	private:
		Configurations m_Configurations;
		std::unordered_map<std::string, Ref<Texture2D>> m_Textures;
	};
}