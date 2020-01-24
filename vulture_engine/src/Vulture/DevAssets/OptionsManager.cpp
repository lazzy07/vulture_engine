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
					std::string id = ele.first + "###" + ele.first + "_selectmat";
					if (ImGui::BeginCombo(id.c_str(), ele.second->GetName().c_str())) {
						for (auto e : *Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetAll()) {
							std::string selectId = e.second->GetName() + "###" + e.second->GetName() + ele.first + "_selctablemat";
							if (ImGui::Selectable(selectId.c_str(), ele.second->GetName() == e.first)) {
								model->GetMaterials()->at(ele.first) = e.second;
							};
						}
						VUL_CORE_TRACE("{0} s material {1}", ele.first, ele.second->GetName());
						ImGui::EndCombo();
					}
				}
				ImGui::Unindent();
				ImGui::Text("Add a new instance to the scene");
				ImGui::Indent();
				if (ImGui::Button("Add an instance###addmodelinstance")) {
					Application::Get().GetCurrentLevel()->AddModelToLevel(Outliner::GetSelectedObject());
				}
				ImGui::Unindent();
			}
			ImGui::EndChild();
		}
		else if (Outliner::GetSelectedMaterial() != "") {
			ImGui::BeginChild("MaterialOptions");
			{
				//Material name
				{
					ImGui::Text("Selected material : ");
					ImGui::SameLine();
					std::string id = Outliner::GetSelectedMaterial();
					ImGui::Text(id.c_str());
				}
				// Adding variables / delete variables
				{
					if (ImGui::Button("Add new variable")) {
						ImGui::OpenPopup("AddNewVariable");
					}

					if(ImGui::BeginPopup("AddNewVariable")){
						const char* vartypes[] = { "Float", "Vec2", "Vec3", "Vec4", "Mat3", "Mat4" };
						static int selected = 0;
						static char name[1000] = "";

						if (ImGui::BeginCombo("SetVariable", vartypes[selected])) {
							{
								int i = 0;
								for (auto var : vartypes) {
									if (ImGui::Selectable(var, selected == i)) {
										selected = i;
									}
									i++;
								}
							}
							ImGui::EndCombo();
						}
						{
							ImGui::InputText("Var Name", name, 1000);
						}
						{
							if (ImGui::Button("Add")) {
								std::string nm = name;
								if (nm != "") {
									Ref<Material> mat = Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(Outliner::GetSelectedMaterial());
									std::string ty = vartypes[selected];

									if (ty == "Float") {
										mat->SetFloat(name, 0.0f);
									}
									else if (ty == "Vec2") {
										mat->SetVec2(nm, glm::vec2(0.0f));
									}
									else if (ty == "Vec3") {
										mat->SetVec3(nm, glm::vec3(0.0f));
									}
									else if (ty == "Vec4") {
										mat->SetVec4(nm, glm::vec4(0.0f));
									}
									else if (ty == "Mat3") {
										mat->SetMat3(nm, glm::mat3(0.0f));
									}
									else if (ty == "Mat4") {
										mat->SetMat4(nm, glm::mat4(0.0f));
									}
									mat->LoadVariables();
									ImGui::CloseCurrentPopup();
									name[0] = '\0';
								}
							}

							if (ImGui::Button("Cancel")) {
								name[0] = '\0';
								ImGui::CloseCurrentPopup();
							}
						}
						ImGui::EndPopup();
					}
				}
			}
			{
				ImGui::BeginGroup();
				{
					Ref<Material> mat = Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(Outliner::GetSelectedMaterial());
					if (mat->GetFloats()->size() > 0) {
						ImGui::Text("Floats");
						for (auto elem : *mat->GetFloats()) {
							ImGui::InputFloat(elem.first.c_str(), &mat->GetFloats()->at(elem.first));
						}
					}
				}
				ImGui::EndGroup();

				ImGui::BeginGroup();
				{
					Ref<Material> mat = Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(Outliner::GetSelectedMaterial());
					if (mat->GetVec2s()->size() > 0) {
						ImGui::Text("Vec2s");
						for (auto elem : *mat->GetVec2s()) {
							ImGui::InputFloat2(elem.first.c_str(), glm::value_ptr(mat->GetVec2s()->at(elem.first)));
						}
					}
				}
				ImGui::EndGroup();

				ImGui::BeginGroup();
				{
					Ref<Material> mat = Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(Outliner::GetSelectedMaterial());
					if (mat->GetVec3s()->size() > 0) {
						ImGui::Text("Vec3s");
						for (auto elem : *mat->GetVec3s()) {
							ImGui::InputFloat3(elem.first.c_str(), glm::value_ptr(mat->GetVec3s()->at(elem.first)));
						}
					}
				}
				ImGui::EndGroup();

				ImGui::BeginGroup();
				{
					Ref<Material> mat = Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(Outliner::GetSelectedMaterial());
					if (mat->GetVec4s()->size() > 0) {
						ImGui::Text("Vec4s");
						for (auto elem : *mat->GetVec4s()) {
							ImGui::InputFloat4(elem.first.c_str(), glm::value_ptr(mat->GetVec4s()->at(elem.first)));
						}
					}
				}
				ImGui::EndGroup();
			}
			{
				ImGui::BeginGroup();
				{

				}
				ImGui::EndGroup();
			}
			ImGui::EndChild();
		}
		else if (Outliner::GetSelectedShader() != "") {

		}
		else if (Outliner::GetSelectedTexture() != "") {

		}
		ImGui::End();
	}

	void OptionsManager::SetCurrent()
	{

	}
}
