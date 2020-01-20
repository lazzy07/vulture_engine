#include "vulpch.h"
#include "Outliner.h"

#include <imgui.h>
#include "Vulture/Core/Application.h"
#include <glm/gtx/string_cast.hpp>

namespace Vulture {
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
		UpdateOutliner();
		ImGui::Begin("Scene Outliner");
		if (ImGui::CollapsingHeader("Objects & Instances")) {
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
		ImGui::End();
	}
	void Outliner::UpdateOutliner()
	{
		Ref<Level> currentLevel = Application::Get().GetCurrentLevel();
		std::unordered_map<std::string, Ref<LevelModelData>>* instances = currentLevel->GetInstanceData();

		m_Instances.clear();

		for (auto elem : *instances) {
			m_Instances[elem.second->Name].push_back(elem.second);
		}
	}
}