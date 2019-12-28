#include "vulpch.h"
#include "Configurations.h"

namespace Vulture {
	Configurations::Configurations()
	{
	}

	Configurations::~Configurations()
	{
	}

	bool Configurations::IsSectionExists(const std::string section)
	{
		return m_Config.find(section) != m_Config.end();
	}

	bool Configurations::IsKeyExists(const std::string section, const std::string key)
	{
		if (IsSectionExists(section)) {
			return m_Config[section].find(key) != m_Config[section].end();
		}
		return false;
	}

	int Configurations::GetInt(const std::string section, const std::string key, const int defaultValue)
	{
		if (IsKeyExists(section, key)) {
			std::string val = m_Config[section][key];
			return std::stoi(val);
		}
		return defaultValue;
	}

	float Configurations::GetFloat(const std::string section, const std::string key, const int defaultValue)
	{
		if (IsKeyExists(section, key)) {
			std::string val = m_Config[section][key];
			return std::stof(val);
		}
		return defaultValue;
	}

	std::string Configurations::GetString(const std::string section, const std::string key, const std::string defaultValue)
	{
		if (IsKeyExists(section, key)) {
			return m_Config[section][key];
		}
		return defaultValue;
	}

	glm::mat3 Configurations::GetMat3(const std::string section, const std::string key, const glm::mat3 defaultValue)
	{
		glm::mat3 mat = defaultValue;

		if (GetString(section, key, "u") != "u") {
			for (unsigned int i = 0; i < 3; i++) {
				for (unsigned int j = 0; j < 3; j++) {
					mat[i][j] = std::stof(m_Config[section][key + std::to_string(i + j)]);
				}
			}
			return mat;
		}

		return defaultValue;
	}

	glm::mat4 Configurations::GetMat4(const std::string section, const std::string key, const glm::mat4 defaultValue)
	{
		glm::mat4 mat = defaultValue;

		if (GetString(section, key, "u") != "u") {
			for (unsigned int i = 0; i < 4; i++) {
				for (unsigned int j = 0; j < 4; j++) {
					mat[i][j] = std::stof(m_Config[section][key + std::to_string(i + j)]);
				}
			}
			return mat;
		}

		return defaultValue;
	}

	bool Configurations::SetInt(const std::string section, const std::string key, int val)
	{
		m_Config[section][key] = std::to_string(val);
		return true;
	}

	bool Configurations::SetFloat(const std::string section, const std::string key, float val)
	{
		m_Config[section][key] = std::to_string(val);
		return true;
	}

	bool Configurations::SetString(const std::string section, const std::string key, std::string val)
	{
		m_Config[section][key] = val;
		return true;
	}

	bool Configurations::SetMat3(const std::string section, const std::string key, glm::mat3 val)
	{
		for (unsigned int i = 0; i < 3; i++) {
			for (unsigned int j = 0; j < 3; j++) {
				m_Config[section][key + std::to_string(i+j)] = val[i][j];
			}
		}
		return true;
	}

	bool Configurations::SetMat4(const std::string section, const std::string key, glm::mat4 val)
	{
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				m_Config[section][key + std::to_string(i + j)] = val[i][j];
			}
		}
		return true;
	}

	std::string Configurations::GetConfigBuffer()
	{
		std::string result = "";
		if (m_Config.size() != 0) {
			for (std::pair<std::string, std::unordered_map<std::string, std::string>> section : m_Config) {
				result.append("[" + section.first + "]\n");
				for (std::pair<std::string, std::string> elem : m_Config[section.first]) {
					result.append(elem.first + "=" + elem.second + "\n");
				}
			}
		}
		return result;
	}

	void Configurations::LoadConfigBuffer(const char * buffer)
	{
		std::string s = buffer;
		std::vector<std::string> vec;

		std::string delimiter = "\n";
		size_t pos = 0;
		std::string token;

		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			vec.push_back(token);
			s.erase(0, pos + delimiter.length());
		}

		std::string currSection = "";

		for (unsigned int i = 0; i < vec.size(); i++) {
			if (vec[i][0] == '[') {
				currSection = vec[i].substr(1, vec[i].find("]") -1);
			}
			else {
				if (currSection != "" && vec[i].size() > 0) {
					std::string key = vec[i].substr(0, vec[i].find("="));
					std::string val = vec[i].substr(vec[i].find("=") + 1);
					
					m_Config[currSection][key] = val;
				}
			}
		}
	}
}