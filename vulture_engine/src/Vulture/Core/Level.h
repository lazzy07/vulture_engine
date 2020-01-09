#pragma once

#include "Vulture/Renderer/ModelLibrary.h"
#include "Vulture/Renderer/MaterialLibrary.h"
#include "Vulture/Renderer/ShaderLibrary.h"
#include "Vulture/Renderer/TextureLibrary.h"

namespace Vulture {
	class Level {
	public:
		Level(std::string name);
		~Level();

		void LoadLevel();
		void SaveLevel();
	private:
		void LoadTextures(const char* textureBuffer);
		void LoadShaders(const char* shaderBuffer);
		void LoadMaterials(const char* materialBuffer);
		void LoadModels(const char* modelBuffer);

	private:
		Ref<ModelLibrary> m_ModelLibrary;
		Ref<MaterialLibrary> m_MaterialLibrary;
		Ref<ShaderLibrary> m_ShaderLibrary;
		Ref<TextureLibrary> m_TextureLibrary;

		std::string m_LevelName;
	};
}