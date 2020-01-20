#pragma once

#include "Vulture/Renderer/ModelLibrary.h"
#include "Vulture/Renderer/MaterialLibrary.h"
#include "Vulture/Renderer/ShaderLibrary.h"
#include "Vulture/Renderer/TextureLibrary.h"
#include "Vulture/Renderer/Camera.h"

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

		void AddModelToLevel(std::string name, glm::vec3 position = glm::vec3(0.0f),
			glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f),
			bool isStatic = true, bool hidden=false);

		//The model as FBX
		void AddNewModel(std::string modelPath);
		//A material with no variables and default shader will be created
		void AddNewMaterial(std::string materialName);
		//Texture will be loaded into the level's textureLibrary (make sure to copy textures to texture folder first)
		void AddNewTexture(std::string texturePath);
		//A new shader will be loaded into the level's shaderLibrary
		void AddNewShader(std::string shaderName);

		void Render(Ref<Camera> camera);
	private:
		void LoadTextures(const char* textureBuffer);
		void LoadShaders(const char* shaderBuffer);
		void LoadMaterials(const char* materialBuffer);
		void LoadModels(const char* modelBuffer);
		void ModelInstancesToConfig();
		void ConfigToModelInstances();


		std::string GetFileName(std::string path);
	private:
		std::string m_LevelName;
		
		Configurations m_Config;

		Ref<ModelLibrary> m_ModelLibrary;
		Ref<MaterialLibrary> m_MaterialLibrary;
		Ref<ShaderLibrary> m_ShaderLibrary;
		Ref<TextureLibrary> m_TextureLibrary;

		glm::vec3 m_PlayerPosition;
		glm::vec3 m_CameraPosition;

		int id;

		struct LevelModelData {
			std::string Name;
			glm::vec3 Position;
			glm::vec3 Rotation;
			glm::vec3 Scale;
			bool IsStatic;
			bool Hidden;
		};

		std::unordered_map<std::string, Ref<LevelModelData>> m_ModelData;
	};
}