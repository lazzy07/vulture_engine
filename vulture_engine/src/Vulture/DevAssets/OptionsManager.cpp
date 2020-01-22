#include "vulpch.h"
#include "OptionsManager.h"

#include "Outliner.h"
#include "Vulture/Core/Application.h"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

namespace Vulture {
	OptionsManager::OptionsManager() : Layer("InstanceManager")
	{

	}

	OptionsManager::~OptionsManager()
	{

	}

	void OptionsManager::OnAttach()
	{

	}

	void OptionsManager::OnDetach()
	{

	}

	void OptionsManager::OnImGuiRender()
	{
		SetCurrent();
		ImGui::Begin("Options Manager");
		if (Outliner::GetSelectedInstance() != "") {
			std::unordered_map<std::string, Ref<LevelModelData>> data = *Application::Get().GetCurrentLevel()->GetInstanceData();
			Ref<LevelModelData> md = data.at(Outliner::GetSelectedInstance());
			ImGui::BeginChild("Translations");
			{
				ImGui::Text("Set Translations");

				ImGui::SliderFloat3("Position Slider", glm::value_ptr(md->Position), -100, 100);
				ImGui::SliderFloat3("Rotation Slider", glm::value_ptr(md->Rotation), -360, 360);
				ImGui::SliderFloat3("Scale Slider", glm::value_ptr(md->Scale), -10, 10);
				
				ImGui::InputFloat3("Position", glm::value_ptr(md->Position));
				ImGui::InputFloat3("Rotation", glm::value_ptr(md->Rotation));
				ImGui::InputFloat3("Scale", glm::value_ptr(md->Scale));
			}
			ImGui::EndChild();
		}
		else if (Outliner::GetSelectedObject() != "") {
			ImGui::BeginChild("Object Options");
			{
				ImGui::Text("Set Materials");
				Ref<Model> model = Application::Get().GetCurrentLevel()->GetModelLibrary()->GetModel(Outliner::GetSelectedObject());
				ImGui::Indent();
				
				for (auto ele : *model->GetMaterials()) {
					if (ImGui::BeginCombo(ele.first.c_str(), ele.second->GetName().c_str())) {
						for (auto e : *Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetAll()) {
							if (ImGui::Selectable(e.second->GetName().c_str(), ele.second->GetName() == e.second->GetName())) {
								ele.second = e.second;
							};
						}
						ImGui::EndCombo();
					}
				}
				ImGui::Unindent();
			}
			ImGui::EndChild();
		}
		ImGui::End();
	}

	void OptionsManager::SetCurrent()
	{

	}
}
