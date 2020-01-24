#include "vulpch.h"
#include "Outliner.h"

#include <imgui.h>
#include "Vulture/Core/Application.h"
#include <glm/gtx/string_cast.hpp>

namespace Vulture {
	std::string Outliner::m_SelectedInstance = "";
	std::string Outliner::m_SelectedObject = "";
	std::string Outliner::m_SelectedMaterial= "";
	std::string Outliner::m_SelectedShader = "";
	std::string Outliner::m_SelectedTexture = "";

	Outliner::Outliner()
	{
	}

	Outliner::~Outliner()
	{
	}

	void Outliner::OnAttach()
	{
		
	}

	void Outliner::OnDetach()
	{
	}

	void Outliner::OnImGuiRender()
	{
		Ref<ModelLibrary> modelLibrary = Application::Get().GetCurrentLevel()->GetModelLibrary();
		UpdateOutliner();
		ImGui::Begin("Scene Outliner");

		if(ImGui::CollapsingHeader("Objects")){
			ImGui::Indent();
			for (auto elem : modelLibrary->GetLibrary()) {
				std::string id = elem.first + "###" +elem.first + "_obj";
				if (ImGui::Selectable(id.c_str(), m_SelectedObject == elem.first)) {
					m_SelectedObject = elem.first;
					m_SelectedInstance = "";
					m_SelectedMaterial = "";
					m_SelectedShader = "";
					m_SelectedTexture = "";
				}
			}
			ImGui::Unindent();
		}
		if (ImGui::CollapsingHeader("Instances")) {
			for (auto elem : m_Instances) {
				if (ImGui::TreeNode(elem.first.c_str())) {
					ImGui::Indent();
					for (auto ins : elem.second) {
						bool selected = ins->Hidden == 0 ? true : false;
						std::string name = ins->Name + "_instance(" + glm::to_string(ins->Position) + ")";
						std::string check_id = "###" + ins->Id;
						ImGui::Checkbox(check_id.c_str(), &selected);
						ImGui::SameLine();
						std::string select_id = name + "###" + name + ins->Id;

						if (ImGui::Selectable(select_id.c_str(), ins->Id == m_SelectedInstance)) {
							m_SelectedInstance = ins->Id;
							m_SelectedObject = "";
							m_SelectedMaterial = "";
							m_SelectedShader = "";
							m_SelectedTexture = "";
							ins->Selected = true;
						}
						else {
							ins->Selected = false;
						}
						ins->Hidden = selected ? 0 : 1;
					}
					ImGui::TreePop();
					ImGui::Unindent();
				}
			}
		};
		if (ImGui::CollapsingHeader("Materials")) {
			ImGui::Indent();
			for (auto elem : *Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetAll()) {
				std::string id = elem.first + "###" + elem.first + ".mat";
				if (ImGui::Selectable(id.c_str(), m_SelectedMaterial == elem.first)) {
					m_SelectedObject = "";
					m_SelectedInstance = "";
					m_SelectedMaterial = elem.first;
					m_SelectedShader = "";
					m_SelectedTexture = "";
				}
			}
			ImGui::Unindent();
		}
		if (ImGui::CollapsingHeader("Shaders")) {
			ImGui::Indent();
			for (auto elem : *Application::Get().GetCurrentLevel()->GetShaderLibrary()->GetAll()) {
				std::string id = elem.first + "###" + elem.first + ".shader";
				if (ImGui::Selectable(id.c_str(), m_SelectedShader == elem.first)) {
					m_SelectedObject = "";
					m_SelectedInstance = "";
					m_SelectedMaterial = "";
					m_SelectedShader = elem.first;
					m_SelectedTexture = "";
				}

			}
			ImGui::Unindent();
		}
		if (ImGui::CollapsingHeader("Textures")) {
			ImGui::Indent();
			for (auto elem : *Application::Get().GetCurrentLevel()->GetTextureLibrary()->GetAll()) {
				std::string id = elem.first + "###" + elem.first + ".shader";
				if (ImGui::Selectable(id.c_str(), m_SelectedShader == elem.first)) {
					m_SelectedObject = "";
					m_SelectedInstance = "";
					m_SelectedMaterial = "";
					m_SelectedShader = "";
					m_SelectedTexture = elem.first;
				}
			}
			ImGui::Unindent();
		}
		ImGui::End();
	}
	void Outliner::UpdateOutliner()
	{
		std::unordered_map<std::string, Ref<LevelModelData>>* instances = Application::Get().GetCurrentLevel()->GetInstanceData();

		m_Instances.clear();

		for (auto elem : *instances) {
			m_Instances[elem.second->Name].push_back(elem.second);
		}
	}
}