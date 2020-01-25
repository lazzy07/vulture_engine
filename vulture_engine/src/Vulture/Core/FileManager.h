#pragma once

namespace Vulture {
	class FileManager {
	public:
		FileManager();
		~FileManager();

		void GetFileList(std::string path, std::string fileType, std::vector<std::string> *filePaths);
		void GetFileList(std::string path, std::string fileType, std::unordered_map<std::string, std::string> *filePaths);

		static bool ISFileExists(const std::string& path);

		static std::string GetFileName(std::string path);
	};
}