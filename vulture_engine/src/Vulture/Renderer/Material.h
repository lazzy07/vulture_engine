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
		inline Configurations GetConfigurations() const { return m_Configurations; };

		void SetFloat(std::string type, std::string name, float value);
		void SetVec2(std::string type, std::string name, glm::vec2 value);
		void SetVec3(std::string type, std::string name, glm::vec3 value);
		void SetVec4(std::string type, std::string name, glm::vec4 value);
		void SetMat3(std::string type, std::string name, glm::mat3 value);
		void SetMat4(std::string type, std::string name, glm::mat4 value);


	private:
		std::string m_Name;
		Configurations m_Configurations;
		Ref<ShaderLibrary> m_Shaders;
	};
}