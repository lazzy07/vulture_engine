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
		
		inline Ref<MaterialLibrary> GetMaterialLibrary() const { return m_MaterialLibrary; };
		inline Ref<ShaderLibrary> GetShaderLibrary() const { return m_ShaderLibrary; };
		inline Ref<TextureLibrary> GetTextureLibrary() const { return m_TextureLibrary; };

		//The model as FBX
		void AddNewModel(std::string modelPath);
		//A material with no variables and default shader will be created
		void AddNewMaterial(std::string materialName);
		//Texture will be loaded into the level's textureLibrary (make sure to copy textures to texture folder first)
		void AddNewTexture(std::string texturePath);
		//A new shader will be loaded into the level's shaderLibrary
		void AddNewShader(std::string shaderName);
	private:
		void LoadTextures(const char* textureBuffer);
		void LoadShaders(const char* shaderBuffer);
		void LoadMaterials(const char* materialBuffer);
		void LoadModels(const char* modelBuffer);
		
		std::string GetFileName(std::string path);
	private:
		Ref<ModelLibrary> m_ModelLibrary;
		Ref<MaterialLibrary> m_MaterialLibrary;
		Ref<ShaderLibrary> m_ShaderLibrary;
		Ref<TextureLibrary> m_TextureLibrary;

		glm::vec3 m_PlayerPosition;
		glm::vec3 m_CameraPosition;

		int id;


		std::string m_LevelName;
	};
}