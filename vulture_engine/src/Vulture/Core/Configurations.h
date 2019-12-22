#pragma once
#include <unordered_map>

namespace Vulture {
	class Configurations {
	public:
		Configurations();
		~Configurations();

		bool isSectionExists(const std::string section);
		bool isKeyExists(const std::string section, const std::string key);

		int getInt(const std::string section, const std::string key, const int defaultValue = -1);
		float getFloat(const std::string section, const std::string key, const int defaultValue = -1.0f);
		std::string getString(const std::string section, const std::string key, const std::string defaultValue = "unknown");

		bool setInt(const std::string section, const std::string key, int val);
		bool setFloat(const std::string section, const std::string key, float val);
		bool setString(const std::string section, const std::string key, std::string val);

		std::string getConfigBuffer();
		void loadConfigBuffer(const char* buffer);
	private:
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_Config;
	};
}