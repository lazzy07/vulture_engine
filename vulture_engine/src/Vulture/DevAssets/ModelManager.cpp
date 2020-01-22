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
			if (ImGui::Button("Add to scene###ModelAddToScene")) {
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
			if (!Application::Get().GetCurrentLevel()->GetModelLibrary()->GetModel(FileManager::GetFileName(m_ModelList[m_Selected]))) {
				Application::Get().GetCurrentLevel()->AddNewModel(FileManager::GetFileName(m_ModelList[m_Selected]));
			} else {
				VUL_CORE_WARN("The Model is already added to the scene: {0} ", FileManager::GetFileName(m_ModelList[m_Selected]));
			}
		}
		else {
			VUL_CORE_WARN("Select a file first");
		}
		
	}
}