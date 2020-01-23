#include "vulpch.h"
#include "MaterialManager.h"

#include "Vulture/Core/Application.h"
#include "imgui.h"


namespace Vulture {
	MaterialManager::MaterialManager() : Layer("MaterialManager")
	{
	}

	MaterialManager::~MaterialManager()
	{
	}

	void MaterialManager::OnAttach()
	{
		UpdateList();
	}

	void MaterialManager::OnDetach()
	{
	}

	void MaterialManager::OnImGuiRender()
	{
		ImGui::Begin("MaterialManager");
		{
			ImGui::ListBoxHeader("###MaterialList");
			{
				for (int i = 0; i < m_MaterialList.size(); i++) {
					if (ImGui::Selectable(FileManager::GetFileName(m_MaterialList[i]).c_str(), m_Selected == i)) {
						m_Selected = i;
					}
				}
			}
			ImGui::ListBoxFooter();
			{
				if (ImGui::Button("Add to Level###MaterialAddToLevel")) {
					AddMaterialToLevel();
				}
				ImGui::SameLine();
				if (ImGui::Button("Update List###UpdateMaterialList")) {
					UpdateList();
				}
				ImGui::SameLine();
				if (ImGui::Button("Add new Material")) {
					ImGui::OpenPopup("Material Import Popup");
				}
			}
			{
				if (ImGui::BeginPopup("Material Import Popup")) {
					ImGui::InputText("Name of Material", m_NewFile, 1000);
					if (ImGui::Button("Add to Level###AddMaterialtolevel")) {
						if (strlen(m_NewFile) > 0) {
							if (!Application::Get().GetCurrentLevel()->GetMaterialLibrary()->Exists(m_NewFile)) {
								Application::Get().GetCurrentLevel()->AddNewMaterial(m_NewFile);
								Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(m_NewFile)->SaveMaterial();
								UpdateList();
							}
						}
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

	void MaterialManager::UpdateList()
	{
		m_MaterialList.clear();
		m_FileManager.GetFileList("./assets/materials", "vulmat", &m_MaterialList);
	}

	void MaterialManager::AddMaterialToLevel()
	{
		if (m_Selected > 0 && m_Selected < m_MaterialList.size()) {
			Application::Get().GetCurrentLevel()->AddNewMaterial(m_MaterialList[m_Selected]);
		}
		else {
			VUL_CORE_WARN("Material is not valid or a material wasn't selected");
		}
	}
}