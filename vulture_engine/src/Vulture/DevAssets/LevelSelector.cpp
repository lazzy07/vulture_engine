#include "vulpch.h"

#include <filesystem>

#include "LevelSelector.h"

namespace Vulture {
	LevelSelector::LevelSelector() : Layer("LevelSelector")
	{
	}
	void LevelSelector::OnAttach()
	{
		SetLevelFiles();
	}

	void LevelSelector::OnDetach()
	{
	}

	void LevelSelector::OnImGuiRender()
	{
		ImGui::Begin("Level Selector");
		std::vector<char*> vc;
		std::transform(m_LevelNames.begin(), m_LevelNames.end(), std::back_inserter(vc), Convert);
		ImGui::ListBox("Available Levels", m_CurrentLevel, vc.data(), vc.size(), 10);

		ImGui::Button("Load Level");
		ImGui::Button("Add Level");

		ImGui::End();
	}

	void LevelSelector::AddNewLevel(std::string levelName)
	{
		m_LevelNames.push_back(levelName);
	}

	std::string LevelSelector::getFileName(const std::string path)
	{
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		std::string name = path.substr(lastSlash, count);
		return name;
	}

	void LevelSelector::SetLevelFiles()
	{
		std::string path = "./assets/levels";
		for (const auto &entry : std::filesystem::directory_iterator(path)) {
			std::string p = entry.path().string();
			auto lastDot = p.rfind('.');
			std::string fileType = p.substr(lastDot+1);

			if (fileType == "vullevel") {
				VUL_CORE_TRACE("Level File Found : {0}", p);
				m_LevelNames.push_back(getFileName(p));
			}
		}
	}
	char * LevelSelector::Convert(const std::string & s)
	{
		char *pc = new char[s.size() + 1];
		std::strcpy(pc, s.c_str());
		return pc;
	}
}