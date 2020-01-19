#include "vulpch.h"
#include "Level.h"

#include <zip/zip.h>
#include <Vulture/Renderer/ModelLoader.h>

namespace Vulture {
	Level::Level(std::string name) : m_LevelName(name)
	{
		m_ModelLibrary.reset(new ModelLibrary());
		m_TextureLibrary.reset(new TextureLibrary());
		m_ShaderLibrary.reset(new ShaderLibrary());
		m_MaterialLibrary.reset(new MaterialLibrary(m_ShaderLibrary, m_TextureLibrary));
	}

	Level::~Level()
	{
	}

	void Level::LoadLevel()
	{
		std::string fileName = "./assets/levels/" + m_LevelName + ".vullevel";
		char* textureBuffer;
		char* shaderBuffer;
		char* materialBuffer;
		char* modelBuffer;

		struct zip_t* zip = zip_open(fileName.c_str(), 0, 'r');
		{
			zip_entry_open(zip, "textures");
			{
				size_t bufsize = zip_entry_size(zip);
				textureBuffer = (char*)malloc(bufsize);
				LoadTextures(textureBuffer);
			}
			zip_entry_close(zip);

			zip_entry_open(zip, "shaders");
			{
				size_t bufsize = zip_entry_size(zip);
				shaderBuffer = (char*)malloc(bufsize);
				LoadShaders(shaderBuffer);
			}
			zip_entry_close(zip);

			zip_entry_open(zip, "materials");
			{
				size_t bufsize = zip_entry_size(zip);
				materialBuffer = (char*)malloc(bufsize);
				LoadMaterials(materialBuffer);
			}
			zip_entry_close(zip);

			zip_entry_open(zip, "models");
			{
				size_t bufsize = zip_entry_size(zip);
				modelBuffer = (char*)malloc(bufsize);
				LoadModels(modelBuffer);
			}
			zip_entry_close(zip);
		}

		zip_close(zip);

		free(textureBuffer);
		free(shaderBuffer);
		free(materialBuffer);
		free(modelBuffer);
	}

	void Level::SaveLevel()
	{
		std::string fileName = "./assets/levels/" + m_LevelName + ".vullevel";

		const char* textureBuffer = m_TextureLibrary->TexturesToConfigBuffer().c_str();
		const char* shaderBuffer = m_ShaderLibrary->GetConfigBuffer().c_str();
		const char* materialBuffer = m_MaterialLibrary->MaterialsToConfigBuffer().c_str();
		const char* modelBuffer = m_ModelLibrary->ModelsToConfigBuffer().c_str();

		struct zip_t *zip = zip_open("foo.zip", ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
		{
			zip_entry_open(zip, "textures");
			{
				zip_entry_write(zip, textureBuffer, strlen(textureBuffer));
			}
			zip_entry_close(zip);
			zip_entry_open(zip, "shaders");
			{
				zip_entry_write(zip, shaderBuffer, strlen(shaderBuffer));
			}
			zip_entry_close(zip);
			zip_entry_open(zip, "materials");
			{
				zip_entry_write(zip, materialBuffer, strlen(materialBuffer));
			}
			zip_entry_close(zip);
			zip_entry_open(zip, "models");
			{
				zip_entry_write(zip, modelBuffer, strlen(modelBuffer));
			}
			zip_entry_close(zip);
		}
		zip_close(zip);
	}

	void Level::AddNewModel(std::string modelPath)
	{
		Vulture::ModelLoader::AddNewModel(modelPath);
		ModelLoader::LoadVulModel("./assets/models/" + GetFileName(modelPath) + ".vulmodel", m_ModelLibrary.get());
	}

	void Level::AddNewMaterial(std::string materialName)
	{
		m_MaterialLibrary->AddNewMaterial(materialName);
	}

	void Level::AddNewTexture(std::string texturePath)
	{
		m_TextureLibrary->Load(texturePath);
	}

	void Level::AddNewShader(std::string shaderName)
	{
		m_ShaderLibrary->Load("./assest/shaders/" + shaderName + ".glsl");
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

		for (std::pair<std::string, std::string>ele : modelMap) {
			VUL_CORE_TRACE("Model to Level's ModelLibrary loaded: {0} :: {1}", ele.first, ele.second);
			ModelLoader::LoadVulModel(ele.second, m_ModelLibrary.get());
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