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
		ModelLibrary m_ModelLibrary;
		MaterialLibrary m_MaterialLibrary;
		ShaderLibrary m_ShaderLibrary;
		TextureLibrary m_TextureLibrary;

		std::string m_LevelName;
	};
}