#include "vulpch.h"
#include "Level.h"

#include <zip/zip.h>
#include "Vulture/Renderer/ModelLoader.h"
#include "Vulture/Renderer/Renderer.h"

#include "IdGenerator.h"

namespace Vulture {
	Level::Level(std::string name) : m_LevelName(name)
	{
		m_ModelLibrary.reset(new ModelLibrary());
		m_TextureLibrary.reset(new TextureLibrary());
		m_ShaderLibrary.reset(new ShaderLibrary());
		m_MaterialLibrary.reset(new MaterialLibrary(m_ShaderLibrary, m_TextureLibrary));

		GetShaderLibrary()->Load("./assets/shaders/default.glsl");
		GetMaterialLibrary()->AddNewMaterial("default", "default");
	}

	Level::~Level()
	{
	}

	void Level::LoadLevel()
	{
		std::string fileName = "./assets/levels/" + m_LevelName + ".vullevel";
		VUL_CORE_TRACE("Loading Level : {0} :: {1}", m_LevelName, fileName);
		char* textureBuffer;
		char* shaderBuffer;
		char* materialBuffer;
		char* modelBuffer;
		char* configBuffer;

		struct zip_t* zip = zip_open(fileName.c_str(), 0, 'r');
		{
			zip_entry_open(zip, "textures");
			{
				size_t bufsize = zip_entry_size(zip);
				textureBuffer = (char*)malloc(bufsize);
				zip_entry_noallocread(zip, (void *)textureBuffer, bufsize);
				LoadTextures(textureBuffer);
			}
			zip_entry_close(zip);

			zip_entry_open(zip, "shaders");
			{
				size_t bufsize = zip_entry_size(zip);
				shaderBuffer = (char*)malloc(bufsize);
				zip_entry_noallocread(zip, (void *)shaderBuffer, bufsize);
				LoadShaders(shaderBuffer);
			}
			zip_entry_close(zip);

			zip_entry_open(zip, "materials");
			{
				size_t bufsize = zip_entry_size(zip);
				materialBuffer = (char*)malloc(bufsize);
				zip_entry_noallocread(zip, (void *)materialBuffer, bufsize);
				LoadMaterials(materialBuffer);
			}
			zip_entry_close(zip);

			zip_entry_open(zip, "models");
			{
				size_t bufsize = zip_entry_size(zip);
				modelBuffer = (char*)malloc(bufsize);
				zip_entry_noallocread(zip, (void *)modelBuffer, bufsize);
				LoadModels(modelBuffer);
			}
			zip_entry_close(zip);

			zip_entry_open(zip, "config");
			{
				size_t bufsize = zip_entry_size(zip);
				configBuffer = (char*)malloc(bufsize);
				zip_entry_noallocread(zip, (void *)configBuffer, bufsize);
				m_Config.LoadConfigBuffer(configBuffer);
			}
			zip_entry_close(zip);
		}

		zip_close(zip);
		std::string name = configBuffer;
		ConfigToModelInstances();

		free(textureBuffer);
		free(shaderBuffer);
		free(materialBuffer);
		free(modelBuffer);
		free(configBuffer);
	}

	void Level::SaveLevel()
	{
		std::string fileName = "./assets/levels/" + m_LevelName + ".vullevel";

		ModelInstancesToConfig();

		std::string textureBuffer = m_TextureLibrary->TexturesToConfigBuffer().c_str();
		std::string shaderBuffer = m_ShaderLibrary->GetConfigBuffer().c_str();
		std::string materialBuffer = m_MaterialLibrary->MaterialsToConfigBuffer().c_str();
		std::string modelBuffer = m_ModelLibrary->ModelsToConfigBuffer();
		std::string configBuffer = m_Config.GetConfigBuffer();

		struct zip_t *zip = zip_open(fileName.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
		{
			zip_entry_open(zip, "textures");
			{
				zip_entry_write(zip, textureBuffer.c_str(), strlen(textureBuffer.c_str()));
			}
			zip_entry_close(zip);
			zip_entry_open(zip, "shaders");
			{
				zip_entry_write(zip, shaderBuffer.c_str(), strlen(shaderBuffer.c_str()));
			}
			zip_entry_close(zip);
			zip_entry_open(zip, "materials");
			{
				zip_entry_write(zip, materialBuffer.c_str(), strlen(materialBuffer.c_str()));
			}
			zip_entry_close(zip);
			zip_entry_open(zip, "models");
			{
				zip_entry_write(zip, modelBuffer.c_str(), strlen(modelBuffer.c_str()));
			}
			zip_entry_close(zip);
			zip_entry_open(zip, "config");
			{
				zip_entry_write(zip, configBuffer.c_str(), strlen(configBuffer.c_str()));
			}
			zip_entry_close(zip);
		}
		zip_close(zip);
	}

	void Level::AddModelToLevel(std::string name, glm::vec3 position, glm::vec3 rotation, 
		glm::vec3 scale, bool isStatic, bool hidden)
	{
		auto ml = m_ModelLibrary->GetLibrary();
		for (auto ele : ml) {
			Ref<LevelModelData> levData;
			levData.reset(new LevelModelData());
			std::string id = IdGenerator::GenerateId();

			levData->Id = id;
			levData->Name = name;
			levData->Position = position;
			levData->Rotation = rotation;
			levData->Scale = scale;
			levData->Hidden = hidden;
			levData->IsStatic = isStatic;

			m_ModelData[id] = levData;
		}
	}

	void Level::AddNewModel(std::string modelPath)
	{
		std::string name = GetFileName(modelPath);
		VUL_CORE_INFO("Level {1}:::Model {0} has been added to the library", name, m_LevelName);
		Vulture::ModelLoader::AddNewModel(modelPath);
		ModelLoader::LoadVulModel("./assets/models/" + name + ".vulmodel", m_ModelLibrary.get());
	}

	void Level::AddNewMaterial(std::string materialName)
	{
		VUL_CORE_INFO("Level {1}:::material {0} has been added to the library", materialName, m_LevelName);
		m_MaterialLibrary->AddNewMaterial(materialName);
	}

	void Level::AddNewTexture(std::string texturePath)
	{
		VUL_CORE_INFO("Level {1}:::texture {0} has been added to the library", texturePath, m_LevelName);
		m_TextureLibrary->Load(texturePath);
	}

	void Level::AddNewShader(std::string shaderName)
	{
		m_ShaderLibrary->Load("./assest/shaders/" + shaderName + ".glsl");
	}

	void Level::Render(Ref<Camera> camera)
	{
		Vulture::Renderer::BeginScene(camera);

		for (auto elem : m_ModelData) {
			std::string modelName = elem.second->Name;
			Ref<LevelModelData> data = elem.second;

			Ref<Model> model = m_ModelLibrary->GetModel(modelName);
			if(!data->Hidden)
				model->Draw(data->Position, data->Rotation, data->Scale);
		}

		Vulture::Renderer::EndScene();
	}

	void Level::LoadTextures(const char * textureBuffer)
	{
		Configurations cfg;
		cfg.LoadConfigBuffer(textureBuffer);

		std::unordered_map<std::string, std::string> textureMap;

		cfg.GetAll("textures", &textureMap);

		for (std::pair<std::string, std::string>ele : textureMap) {
			m_TextureLibrary->Load(ele.second);
		}
	}

	void Level::LoadShaders(const char * shaderBuffer)
	{
		Configurations cfg;
		cfg.LoadConfigBuffer(shaderBuffer);

		std::unordered_map<std::string, std::string> shaderMap;

		cfg.GetAll("shaders", &shaderMap);

		for(std::pair<std::string, std::string>ele : shaderMap){
			VUL_CORE_TRACE("Shader to Level's ShaderLibrary loaded: {0} :: {1}", ele.first, ele.second);
			m_ShaderLibrary->Load(ele.second);
		}
	}

	void Level::LoadMaterials(const char * materialBuffer)
	{
		Configurations cfg;
		cfg.LoadConfigBuffer(materialBuffer);

		std::unordered_map<std::string, std::string> materialMap;

		cfg.GetAll("materials", &materialMap);

		for (std::pair<std::string, std::string>ele : materialMap) {
			VUL_CORE_TRACE("Material to Level's materialLibrary loaded: {0} :: {1}", ele.first, ele.second);
			m_MaterialLibrary->Load(ele.second);
		}
	}

	void Level::LoadModels(const char * modelBuffer)
	{
		Configurations cfg;
		cfg.LoadConfigBuffer(modelBuffer);

		std::unordered_map<std::string, std::string> modelMap;
		cfg.GetAll("models", &modelMap);

		for (std::pair<std::string, std::string>ele : modelMap) {
			VUL_CORE_TRACE("Model to Level's ModelLibrary loaded: {0} :: {1}", ele.first, ele.second);
			ModelLoader::LoadVulModel("./assets/models/" + ele.second + ".vulmodel", m_ModelLibrary.get());
		}
	}

	void Level::ModelInstancesToConfig()
	{
		for (auto ele : m_ModelData) {
			Ref<LevelModelData> data = ele.second;
			std::string id = ele.first;

			m_Config.SetString(id, "id", data->Id);
			m_Config.SetString(id, "name", data->Name);
			m_Config.SetVec3(id, "position", data->Position);
			m_Config.SetVec3(id, "rotation", data->Rotation);
			m_Config.SetVec3(id, "scale", data->Scale);
			m_Config.SetInt(id, "isStatic", data->IsStatic);
			m_Config.SetInt(id, "hidden", data->Hidden);

			m_Config.SetString("modelinstances", id, data->Name);
		}
	}

	void Level::ConfigToModelInstances()
	{
		std::unordered_map<std::string, std::string> model_instances;
		m_Config.GetAll("modelinstances", &model_instances);

		for (auto ele : model_instances) {
			std::string id = ele.first;
			std::string name = ele.second;

			glm::vec3 position = m_Config.GetVec3(id, "position");
			glm::vec3 rotation = m_Config.GetVec3(id, "rotation");
			glm::vec3 scale = m_Config.GetVec3(id, "scale");
			int hidden = m_Config.GetInt(id, "hidden");
			int isStatic = m_Config.GetInt(id, "isStatic");

			AddModelToLevel(name, position, rotation, scale, isStatic, hidden);
		}
	}

	std::string Level::GetFileName(std::string path)
	{
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		std::string name = path.substr(lastSlash, count);
		return name;
	}
}