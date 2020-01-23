#include "vulpch.h"
#include "ModelManager.h"

#include "imgui.h"
#include "Vulture/Core/Application.h"

namespace Vulture {
	ModelManager::ModelManager() : Layer("ModelManager")
	{

	}

	ModelManager::~ModelManager()
	{

	}

	void ModelManager::OnAttach()
	{
		UpdateModelList();
		m_NewPath[0] = '\0';
	}

	void ModelManager::OnDetach()
	{

	}

	void ModelManager::OnImGuiRender()
	{
		ImGui::Begin("ModelManager");
		{
			ImGui::ListBoxHeader("###ModelList");
			{
				for (int i = 0; i < m_ModelList.size(); i++) {
					if (ImGui::Selectable(FileManager::GetFileName(m_ModelList[i]).c_str(), m_Selected == i)) {
						m_Selected = i;
					}
				}
			}
			ImGui::ListBoxFooter();
		}
		
		{
			if (ImGui::Button("Add to Level###ModelAddToLevel")) {
				AddModelToLevel();
			}
			ImGui::SameLine();
			if (ImGui::Button("Update List")) {
				UpdateModelList();
			}
			ImGui::SameLine();
			if (ImGui::Button("Import Model")) {
				ImGui::OpenPopup("Model Import Popup");
			}
			{
				if (ImGui::BeginPopup("Model Import Popup")) {
					ImGui::InputText("Path of 3D Model", m_NewPath, 1000);
					if (ImGui::Button("Add to Level###Add3Dtolevel")) {
						Application::Get().GetCurrentLevel()->AddNewModel(m_NewPath);
						UpdateModelList();
						ImGui::CloseCurrentPopup();
					}
					if (ImGui::Button("Cancel###canceladdtolevel")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
			}
		}
		ImGui::End();
	}

	void ModelManager::UpdateModelList()
	{
		m_ModelList.clear();
		m_FileManager.GetFileList("./assets/models", "vulmodel", &m_ModelList);
	}

	void ModelManager::AddModelToLevel()
	{
		if (m_Selected < m_ModelList.size() && m_Selected >= 0) {
			if (!Application::Get().GetCurrentLevel()->GetModelLibrary()->Exists(FileManager::GetFileName(m_ModelList[m_Selected]))) {
				std::string name = FileManager::GetFileName(m_ModelList[m_Selected]);
				Application::Get().GetCurrentLevel()->AddNewModel(name);
			} else {
				VUL_CORE_WARN("The Model is already added to the scene: {0} ", FileManager::GetFileName(m_ModelList[m_Selected]));
			}
		}
		else {
			VUL_CORE_WARN("Select a file first");
		}
		
	}
}