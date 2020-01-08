#pragma once

#include <string>
#include <unordered_map>

#include "Vulture/Core/Core.h"
#include "Shader.h"
#include "Vulture/Core/Configurations.h"

namespace Vulture {
	class ShaderLibrary {
	public:
		ShaderLibrary() {};
		virtual ~ShaderLibrary() = default;
		void Add(const Ref<Shader>& shader, const std::string filePath); //the shader will use the filename as the shader name
		void Add(const std::string& name, const Ref<Shader>& shader, const std::string filePath); //if you need a custom name for the shader other than the filename

		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Load(const std::string& name, const std::string& filePath);
		Ref<Shader> Get(const std::string& name);
		bool Exists(const std::string& name);

		const char* GetConfigBuffer();
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
		Configurations m_Configurations;
	};
}