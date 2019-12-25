#pragma once
#include "Texture.h"


namespace Vulture{
	class TextureLibrary {
	public:
	private:
		std::unordered_map<std::string, Ref<Texture>> m_Textures;
	};
}