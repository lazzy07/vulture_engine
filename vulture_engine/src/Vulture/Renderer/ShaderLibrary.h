#pragma once

#include <string>
#include <unordered_map>

#include "Vulture/Core.h"
#include "Shader.h"

namespace Vulture {
	class ShaderLibrary {
	public:
		ShaderLibrary() {};
		virtual ~ShaderLibrary() = default;
		void Add(const Ref<Shader>& shader); //the shader will use the filename as the shader name
		void Add(const std::string& name, const Ref<Shader>& shader); //if you need a custom name for the shader other than the filename

		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Load(const std::string& name, const std::string& filePath);
		Ref<Shader> Get(const std::string& name);
		bool Exists(const std::string& name);
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}