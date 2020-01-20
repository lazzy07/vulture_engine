#include "vulpch.h"
#include "ShaderLibrary.h"

namespace Vulture {
	void ShaderLibrary::Add(const Ref<Shader>& shader, const std::string filePath)
	{
		auto& name = shader->GetName();
		Add(name, shader, filePath);
	}

	void ShaderLibrary::Add(const std::string & name, const Ref<Shader>& shader, const std::string filePath)
	{
		if (name != "default") {
			VUL_CORE_ASSERT(!Exists(name), "Shader Already exists");
		}
		m_Configurations.SetString("shaders", name, filePath);
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string & filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader, filePath);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Load(const std::string & name, const std::string & filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader, filePath);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Get(const std::string & name)
	{
		VUL_CORE_ASSERT(Exists(name), "Shader couln't be found");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string & name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

	std::string ShaderLibrary::GetConfigBuffer()
	{
		return m_Configurations.GetConfigBuffer();
	}
}