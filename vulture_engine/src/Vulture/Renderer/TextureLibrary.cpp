#include "vulpch.h"
#include "TextureLibrary.h"
#include "Vulture/Core/FileManager.h"

namespace Vulture{
	void TextureLibrary::Load(std::string path)
	{
		std::string name = GetFileName(path);
		m_Configurations.SetString("textures", name, path);
		VUL_CORE_ASSERT(!Exists(name), "Texture2D with same name already exists");
		m_Textures[name] = Texture2D::Create(path);
	}

	Ref<Texture2D> TextureLibrary::GetTexture(std::string name)
	{
		//VUL_CORE_ASSERT(Exists(name), "Cannot find a texture2d with specified name");
		if (Exists(name)) {
			return m_Textures[name];
		}
		else {
			VUL_CORE_INFO("Shader {0} not found, loading...", name);
			FileManager fm;
			std::unordered_map<std::string, std::string> m;

			fm.GetFileList("./assets/textures", "", &m);
			Load(m[name]);
			return m_Textures[name];
		}
	}

	void TextureLibrary::RemoveTexture(std::string name)
	{
		m_Configurations.RemoveEntry("textures", name);
	}

	bool TextureLibrary::Exists(std::string name)
	{
		return m_Textures.find(name) != m_Textures.end();
	}

	std::string TextureLibrary::TexturesToConfigBuffer()
	{
		return m_Configurations.GetConfigBuffer();
	}

	std::string TextureLibrary::GetFileName(std::string path)
	{
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		std::string name = path.substr(lastSlash, count);
		return name;
	}
}