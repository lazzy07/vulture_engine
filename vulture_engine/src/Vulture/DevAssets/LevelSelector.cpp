#include "vulpch.h"

#include <filesystem>
#include "LevelSelector.h"
#include "Vulture/Core/Application.h"
#include "Vulture/DevAssets/Outliner.h"

namespace Vulture {
	LevelSelector::LevelSelector() : Layer("LevelSelector")
	{
	}
	void LevelSelector::OnAttach()
	{
		SetLevelFiles();
		m_NewLevelName[0] = '\0';
	}

	void LevelSelector::OnDetach()
	{
	}

	void LevelSelector::OnImGuiRender()
	{
		ImGui::Begin("Level Selector");
		
		{
			ImGui::Text("Current Level :: ");
			ImGui::SameLine();
			ImGui::Text(m_LevelNames[m_CurrentLevel].c_str());
			ImGui::ListBox("###AvailableLevels", &m_CurrentLevel, vc.data(), vc.size(), 10);
			if (ImGui::Button("Load Level")) {
				std::string name = m_LevelNames[m_CurrentLevel];
				Ref<Level> lev;
				lev.reset(new Level(name));
				lev->LoadLevel();
				Outliner::ResetSelected();
				Application::Get().SetCurrentLevel(lev);
			};
			ImGui::SameLine();
			m_AddLevelButtonStatus = ImGui::Button("Add Level");
			ImGui::SameLine();
			if (ImGui::Button("Save Level")) {

			}
			AddNewLevelDialog();
		}

		ImGui::End();
	}

	bool LevelSelector::AddNewLevel(std::string levelName)
	{
		if (levelName != "") {
			for (std::string ln : m_LevelNames) {
				if (ln == levelName) {
					return false;
				}
			}
			m_LevelNames.push_back(levelName);
			Level level(levelName);
			level.SaveLevel();
			VUL_CORE_TRACE("New Level Added : {0}", levelName);

			vc.clear();
			for (unsigned int i = 0; i < m_LevelNames.size(); i++) {
				vc.push_back(Convert(m_LevelNames[i]));
			}

			return true;
		}
		return false;
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

	void LevelSelector::AddNewLevelDialog()
	{
		if (m_AddLevelButtonStatus || m_OpenAddNewLevelDialog) {
			if (m_AddLevelButtonStatus) {
				VUL_CORE_TRACE("Level popup open");
				m_OpenAddNewLevelDialog = true;
			}

			ImGui::OpenPopup("Add new layer");
			ImGui::BeginPopup("Add new layer");
			{
				ImGui::InputText("Level Name", m_NewLevelName, 500);
				if (ImGui::Button("Add Level")) {
					if (AddNewLevel(m_NewLevelName)) {
						m_OpenAddNewLevelDialog = false;
						ImGui::CloseCurrentPopup();
					}
				}

				if (ImGui::Button("Close")) {
					m_OpenAddNewLevelDialog = false;
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::EndPopup();
		}
	}

	void LevelSelector::SetLevelFiles()
	{
		std::string path = "./assets/levels";
		for (const auto &entry : std::filesystem::directory_iterator(path)) {
			std::string p = entry.path().string();
			auto lastDot = p.rfind('.');
			std::string fileType = p.substr(lastDot+1);

			if (fileType == "vullevel") {
				VUL_CORE_TRACE("DEBUG::LevelLoader::Level File Found : {0}", p);
				m_LevelNames.push_back(getFileName(p));
			}
		}

		for (unsigned int i = 0; i < m_LevelNames.size(); i++) {
			vc.push_back(Convert(m_LevelNames[i]));
		}
	}
	char * LevelSelector::Convert(const std::string & s)
	{
		char *pc = new char[s.size() + 1];
		std::strcpy(pc, s.c_str());
		return pc;
	}
}