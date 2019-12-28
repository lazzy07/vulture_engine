#pragma once
#include "Shader.h"
#include "ShaderLibrary.h"
#include "Vulture/Core/Configurations.h"

namespace Vulture {
	class Material {
	public:
		Material(const std::string name, const std::string shaderName, Ref<ShaderLibrary> shaderLibrary);
		~Material();
		Ref<Shader> GetShader();
		void SetShader(std::string shader);
		inline Configurations GetConfigurations() const { return m_Configurations; }
	private:
		std::string m_Name;
		Configurations m_Configurations;
		Ref<ShaderLibrary> m_Shaders;
	};
}