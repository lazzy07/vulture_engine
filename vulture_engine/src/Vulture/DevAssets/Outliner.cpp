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
	std::string Outliner::m_SelectedLight = "";
	std::string Outliner::m_SelectedLightInstance = "";
	LightTypes Outliner::m_SelectedLightInstanceType = LightTypes::DIRECTIONAL_LIGHT;


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
					m_SelectedLight = "";
					m_SelectedLightInstance = "";
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
							m_SelectedLight = "";
							m_SelectedLightInstance = "";
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
					m_SelectedLight = "";
					m_SelectedLightInstance = "";
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
					m_SelectedLight = "";
					m_SelectedLightInstance = "";
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
					m_SelectedLight = "";
					m_SelectedLightInstance = "";
				}
			}
			ImGui::Unindent();
		}
		if (ImGui::CollapsingHeader("Lights")) {
			const char* const lightTypes[] = { "Directional Light", "Point Light", "Spot Light" };
			ImGui::Indent();
			{
				static int selected = -1;
				if (ImGui::ListBox("Light Types", &selected, lightTypes, 3)) {
					if (selected == 0) {
						ResetSelected();
						m_SelectedLight = "directional";
					}
					else if (selected == 1) {
						ResetSelected();
						m_SelectedLight = "point";
					}
					else if (selected == 2) {
						ResetSelected();
						m_SelectedLight = "spot";
					}
				}
			}
			ImGui::Unindent();
		}
		if (ImGui::CollapsingHeader("Light Instances")) {
			ImGui::Indent();
			{
				auto lib = Application::Get().GetCurrentLevel()->GetLightLibrary();

				if (ImGui::CollapsingHeader("Directional Lights")) {
					for (auto ele : *lib->GetDirectionalLights()) {
						std::string id = "###" + ele->GetId() + "isActive";
						bool isActive = ele->GetIsActive();
						if (ImGui::Checkbox(id.c_str(), &isActive)) {
							ele->SetActive(isActive);
						};
						ImGui::SameLine();
						if (ImGui::Selectable(ele->GetId().c_str(), ele->GetId() == m_SelectedLightInstance)) {
							ResetSelected();
							m_SelectedLightInstanceType = LightTypes::DIRECTIONAL_LIGHT;
							m_SelectedLightInstance = ele->GetId();
						}
					}
				}

				if (ImGui::CollapsingHeader("Point Lights")) {
					for (auto ele : *lib->GetPointLights()) {
						std::string id = "###" + ele->GetId() + "isActive";
						bool isActive = ele->GetIsActive();
						if (ImGui::Checkbox(id.c_str(), &isActive)) {
							ele->SetActive(isActive);
						};
						ImGui::SameLine();
						if (ImGui::Selectable(ele->GetId().c_str(), ele->GetId() == m_SelectedLightInstance)) {
							ResetSelected();
							m_SelectedLightInstanceType = LightTypes::POINT_LIGHT;
							m_SelectedLightInstance = ele->GetId();
						}
					}
				}

				if (ImGui::CollapsingHeader("Spot Lights")) {
					for (auto ele : *lib->GetSpotLights()) {
						std::string id = "###" + ele->GetId() + "isActive";
						bool isActive = ele->GetIsActive();
						if (ImGui::Checkbox(id.c_str(), &isActive)) {
							ele->SetActive(isActive);
						};
						ImGui::SameLine();
						if (ImGui::Selectable(ele->GetId().c_str(), ele->GetId() == m_SelectedLightInstance)) {
							ResetSelected();
							m_SelectedLightInstanceType = LightTypes::SPOT_LIGHT;
							m_SelectedLightInstance = ele->GetId();
						}
					}
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