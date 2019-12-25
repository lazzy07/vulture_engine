#pragma once
#include <unordered_map>

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

		bool SetInt(const std::string section, const std::string key, int val);
		bool SetFloat(const std::string section, const std::string key, float val);
		bool SetString(const std::string section, const std::string key, std::string val);

		std::string GetConfigBuffer();
		void LoadConfigBuffer(const char* buffer);
	private:
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_Config;
	};
}