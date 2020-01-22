#include "vulpch.h"
#include "FileManager.h"

#include <filesystem>

namespace Vulture {
	FileManager::FileManager()
	{
	}

	FileManager::~FileManager()
	{
	}

	void FileManager::GetFileList(std::string path, std::string fileType, std::vector<std::string>* filePaths)
	{
		for (const auto &entry : std::filesystem::directory_iterator(path)) {
			std::string p = entry.path().string();
			auto lastDot = p.rfind('.');
			std::string fileType = p.substr(lastDot + 1);

			if (fileType == fileType) {
				filePaths->push_back(p);
			}
		}
	}

	void FileManager::GetFileList(std::string path, std::string fileType, std::unordered_map<std::string, std::string>* filePaths)
	{
		for (const auto &entry : std::filesystem::directory_iterator(path)) {
			std::string p = entry.path().string();
			auto lastDot = p.rfind('.');
			std::string fileType = p.substr(lastDot + 1);

			if (fileType == fileType) {
				filePaths->insert(std::pair<std::string, std::string>(GetFileName(p), p));
			}
		}
	}

	std::string FileManager::GetFileName(std::string path)
	{
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		std::string name = path.substr(lastSlash, count);
		return name;
	}
}