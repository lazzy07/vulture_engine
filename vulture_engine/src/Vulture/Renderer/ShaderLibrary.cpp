#include "vulpch.h"
#include "ShaderLibrary.h"

namespace Vulture {
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string & name, const Ref<Shader>& shader)
	{
		VUL_CORE_ASSERT(!Exists(name), "Shader Already exists");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string & filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}
	
	Ref<Shader> ShaderLibrary::Load(const std::string & name, const std::string & filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(name, shader);
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
}