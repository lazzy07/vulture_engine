#pragma once
#include "Shader.h"
#include "ShaderLibrary.h"
#include "Vulture/Core/Configurations.h"
#include "Vulture/Renderer/TextureLibrary.h"

namespace Vulture {
	class Material {
	public:
		Material(const std::string name, const std::string shaderName, Ref<ShaderLibrary> shaderLibrary, Ref<TextureLibrary> textureLibrary);
		~Material();
		Ref<Shader> GetShader();
		void SetShader(std::string shader);
		inline Configurations GetConfigurations() const { return m_Configurations; };

		void SetFloat(std::string name, float value);
		void SetVec2(std::string name, glm::vec2 value);
		void SetVec3(std::string name, glm::vec3 value);
		void SetVec4(std::string name, glm::vec4 value);
		void SetMat3(std::string name, glm::mat3 value);
		void SetMat4(std::string name, glm::mat4 value);
		void SetTexture(std::string name, float textureSlot);

		void LoadVariables();
		void Bind();
	private:
		std::unordered_map<std::string, float> m_Floats;
		std::unordered_map<std::string, glm::vec2> m_Vec2s;
		std::unordered_map<std::string, glm::vec3> m_Vec3s;
		std::unordered_map<std::string, glm::vec4> m_Vec4s;

		std::unordered_map<std::string, glm::mat3> m_Mat3s;
		std::unordered_map<std::string, glm::mat3> m_Mat4s;

		std::unordered_map<std::string, float> m_Textures;

		std::string m_Name;
		Configurations m_Configurations;
		Ref<ShaderLibrary> m_ShaderLibrary;
		Ref<TextureLibrary> m_TextureLibrary;
		Ref<Shader> m_Shader;
	};
}