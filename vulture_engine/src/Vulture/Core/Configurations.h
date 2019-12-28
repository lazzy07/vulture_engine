#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

namespace Vulture {
	class Configurations {
	public:
		Configurations();
		~Configurations();

		bool IsSectionExists(const std::string section);
		bool IsKeyExists(const std::string section, const std::string key);

		int GetInt(const std::string section, const std::string key, const int defaultValue = -1);
		float GetFloat(const std::string section, const std::string key, const int defaultValue = -1.0f);
		std::string GetString(const std::string section, const std::string key, const std::string defaultValue = "unknown");
		glm::mat3 GetMat3(const std::string section, const std::string key, const glm::mat3 defaultValue = glm::mat3(0.0f));
		glm::mat4 GetMat4(const std::string section, const std::string key, const glm::mat4 defaultValue = glm::mat4(0.0f));

		bool SetInt(const std::string section, const std::string key, int val);
		bool SetFloat(const std::string section, const std::string key, float val);
		bool SetString(const std::string section, const std::string key, std::string val);
		bool SetMat3(const std::string section, const std::string key, glm::mat3 val);
		bool SetMat4(const std::string section, const std::string key, glm::mat4 val);

		std::string GetConfigBuffer();
		void LoadConfigBuffer(const char* buffer);
	private:
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_Config;
	};
}