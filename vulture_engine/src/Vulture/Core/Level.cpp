#include "vulpch.h"
#include "Level.h"

#include <zip/zip.h>

namespace Vulture {
	Level::Level(std::string name) : m_LevelName(name)
	{
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
	}

	void Level::LoadTextures(const char * textureBuffer)
	{
		Configurations cfg;
		cfg.LoadConfigBuffer(textureBuffer);

		std::unordered_map<std::string, std::string> textureMap;

		cfg.GetAll("textures", &textureMap);

		for (std::pair<std::string, std::string>ele : textureMap) {
			m_ShaderLibrary.Load(ele.second);
		}
	}

	void Level::LoadShaders(const char * shaderBuffer)
	{
		Configurations cfg;
		cfg.LoadConfigBuffer(shaderBuffer);

		std::unordered_map<std::string, std::string> shaderMap;

		cfg.GetAll("shaders", &shaderMap);

		for(std::pair<std::string, std::string>ele : shaderMap){
			m_ShaderLibrary.Load(ele.second);
		}
	}

	void Level::LoadMaterials(const char * materialBuffer)
	{
		Configurations cfg;
		cfg.LoadConfigBuffer(materialBuffer);

		std::unordered_map<std::string, std::string> materialMap;

		cfg.GetAll("materials", &materialMap);

		for (std::pair<std::string, std::string>ele : materialMap) {
			
		}
	}

	void Level::LoadModels(const char * modelBuffer)
	{
	}
}