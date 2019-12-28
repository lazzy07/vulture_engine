#pragma once
#include "Texture.h"


namespace Vulture{
	class TextureLibrary {
	public:
		void Load(std::string path);
		Ref<Texture> GetTexture() const;
		void RemoveTexture(std::string name);

		std::string TexturesToConfigBuffer;

	private:
		std::unordered_map<std::string, Ref<Texture>> m_Textures;
	};
}