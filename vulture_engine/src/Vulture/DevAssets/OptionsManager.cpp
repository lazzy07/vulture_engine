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
			{
				if (ImGui::Button("Save Instances")) {
					Application::Get().GetCurrentLevel()->SaveLevel();
				}
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
								//model->GetMaterials()->at(ele.first) = e.second;
								model->ChangeMaterial(ele.first, e.second->GetName());
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
				ImGui::SameLine();
				if (ImGui::Button("Save Object")) {
					Application::Get().GetCurrentLevel()->SaveLevel();
					Application::Get().GetCurrentLevel()->GetModelLibrary()
						->GetModel(Outliner::GetSelectedObject())->SaveConfig();
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

				{
					if (ImGui::Button("Save Materal")) {
						auto material = Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(Outliner::GetSelectedMaterial());
						material->SaveMaterial();
						Application::Get().GetCurrentLevel()->SaveLevel();
						VUL_CORE_TRACE("Material save complete: {0}", Outliner::GetSelectedMaterial());
					}
				}

				{

					ImGui::Text("Select Shader: ");
					Ref<Material> mat = Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(Outliner::GetSelectedMaterial());

					static std::string selected = mat->GetShader()->GetName();

					if (ImGui::BeginCombo("SetShader", selected.c_str())) {
						{
							for (auto elem : *Application::Get().GetCurrentLevel()->GetShaderLibrary()->GetAll()) {
								std::string id = elem.first + "###" + elem.first + "selshadermat";
								if (ImGui::Selectable(id.c_str(), elem.first == selected)) {
									mat->SetShader(elem.first);
									selected = elem.first;
								}
							}
						}
						ImGui::EndCombo();
					}
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
					if (ImGui::Button("Add Texture")) {
						ImGui::OpenPopup("Add Texture To Material");
					}

					if(ImGui::BeginPopup("Add Texture To Material")){
						{
							static int value = 0;
							static std::string val = "none";
							ImGui::InputInt("Texture Slot", &value);
							
							auto textures = Application::Get().GetCurrentLevel()->GetTextureLibrary()->GetAll();
							if (ImGui::BeginCombo("Select Texture", val.c_str())){
								for (auto ele : *textures) {
									if (ImGui::Selectable(ele.first.c_str(), val == ele.first)) {
										val = ele.first;
									}
								}
								ImGui::EndCombo();
							}

							{
								if (ImGui::Button("Add")) {
									Ref<Material> mat = Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(Outliner::GetSelectedMaterial());
									if (val != "none") {
										mat->SetTexture(val, value);
										mat->LoadVariables();
										value = 0;
										val = "none";
										ImGui::CloseCurrentPopup();
									}
									else {
										VUL_CORE_WARN("Please select a valid texture");
									}
								}
								if (ImGui::Button("Cancel")) {
									val = "none";
									value = 0;
									ImGui::CloseCurrentPopup();
								}
							}
						}
						ImGui::EndPopup();
					}
					{
						Ref<Material> mat = Application::Get().GetCurrentLevel()->GetMaterialLibrary()->GetMaterial(Outliner::GetSelectedMaterial());

						for (auto ele : *mat->GetTextures()) {
							std::string name = ele.first + " at " + std::to_string((int)ele.second);
							ImGui::Text(name.c_str());
							ImGui::SameLine();
							if (ImGui::Button("Delete")) {

							}
						}
					}
				}
				ImGui::EndGroup();
			}
			ImGui::EndChild();
		}
		else if (Outliner::GetSelectedShader() != "") {

		}
		else if (Outliner::GetSelectedTexture() != "") {

		}
		else if (Outliner::GetSelectedLight() != "") {
			ImGui::BeginChild("Light options");
			{
				std::string name = "Create a light options : " + Outliner::GetSelectedLight() + " light";
				ImGui::Text(name.c_str());
				if (ImGui::Button("Create Light")) {
					std::string type = Outliner::GetSelectedLight();
					if (type == "directional")
						Application::Get().GetCurrentLevel()->GetLightLibrary()->AddNewLight(LightTypes::DIRECTIONAL_LIGHT);
					else if (type == "spot")
						Application::Get().GetCurrentLevel()->GetLightLibrary()->AddNewLight(LightTypes::SPOT_LIGHT);
					else if(type == "point")
						Application::Get().GetCurrentLevel()->GetLightLibrary()->AddNewLight(LightTypes::POINT_LIGHT);
				}
			}
			ImGui::EndChild();
		}
		else if (Outliner::GetSelectedLightInstance() != "") {
			auto lightMaterial = Application::Get().GetCurrentLevel()->GetLightLibrary();
			if (Outliner::GetSelectedLightInstanceType() == LightTypes::DIRECTIONAL_LIGHT) {
				Ref<DirectionalLight> light;
				for (auto ele : *lightMaterial->GetDirectionalLights()) {
					if (ele->GetId() == Outliner::GetSelectedLightInstance()) {
						light = ele;
					}
				}

				if (light) {
					ImGui::BeginChild("Directional Lights");
					{
						std::string id = light->GetId() + "###" + light->GetId() + "id";
						std::string id1 = ": Position###" + light->GetId() + "id1";
						std::string id2 = ": Position###" + light->GetId() + "id2";
						ImGui::Text(id.c_str());
						{
							glm::vec3 pos = light->GetPosition();
							if (ImGui::SliderFloat3(id1.c_str(), glm::value_ptr(pos), -100, 100)) {
								light->SetPosition(pos);
							}
							if (ImGui::InputFloat3(id2.c_str(), glm::value_ptr(pos))) {
								light->SetPosition(pos);
							}
						}

						{
							glm::vec3 color = light->GetColor() * glm::vec3(255);
							if (ImGui::ColorEdit3("Light Color", glm::value_ptr(color))) {
								light->SetColor(color / glm::vec3(255.0f));
							}
						}

						{
							if (ImGui::RadioButton("Is Static", light->GetStatic())) {
								light->SetStatic(!light->GetStatic());
							}
						}

						{
							float val = light->GetStrength();
							if (ImGui::DragFloat("Strength", &val, 1.0f, 0.0f, 100.0f)) {
								light->SetStrength(val);
							}
						}

						{
							float val = light->GetAffectiveDistance();

							if (ImGui::DragFloat("Affective Distance", &val, 1.0f, 0.0f, 100.0f)) {
								light->SetAffectiveDistance(val);
							}
						}

						{
							glm::vec3 direction = light->GetDirection();

							if (ImGui::InputFloat3("Direction", glm::value_ptr(direction))) {
								light->SetDirection(direction);
							}
						}
					}
					ImGui::EndChild();
				}
			}
			else if (Outliner::GetSelectedLightInstanceType() == LightTypes::POINT_LIGHT) {
				Ref<PointLight> light;
				for (auto ele : *lightMaterial->GetPointLights()) {
					if (ele->GetId() == Outliner::GetSelectedLightInstance()) {
						light = ele;
					}
				}

				if (light) {
					ImGui::BeginChild("Point Lights");
					{
						std::string id = light->GetId() + "###" + light->GetId() + "id";
						std::string id1 = ": Position###" + light->GetId() + "id1";
						std::string id2 = ": Position###" + light->GetId() + "id2";
						ImGui::Text(id.c_str());
						{
							glm::vec3 pos = light->GetPosition();
							if (ImGui::SliderFloat3(id1.c_str(), glm::value_ptr(pos), -100, 100)) {
								light->SetPosition(pos);
							}
							if (ImGui::InputFloat3(id2.c_str(), glm::value_ptr(pos))) {
								light->SetPosition(pos);
							}
						}

						{
							glm::vec3 color = light->GetColor() * glm::vec3(255);
							if (ImGui::ColorEdit3("Light Color", glm::value_ptr(color))) {
								light->SetColor(color / glm::vec3(255.0f));
							}
						}

						{
							if (ImGui::RadioButton("Is Static", light->GetStatic())) {
								light->SetStatic(!light->GetStatic());
							}
						}

						{
							float val = light->GetStrength();
							if (ImGui::DragFloat("Strength", &val, 1.0f, 0.0f, 100.0f)) {
								light->SetStrength(val);
							}
						}

						{
							float val = light->GetAffectiveDistance();

							if (ImGui::DragFloat("Affective Distance", &val, 1.0f, 0.0f, 100.0f)) {
								light->SetAffectiveDistance(val);
							}
						}
					}
					ImGui::EndChild();
				}
			}
			else if (Outliner::GetSelectedLightInstanceType() == LightTypes::SPOT_LIGHT) {
				Ref<SpotLight> light;
				for (auto ele : *lightMaterial->GetSpotLights()) {
					if (ele->GetId() == Outliner::GetSelectedLightInstance()) {
						light = ele;
					}
				}

				if (light) {
					ImGui::BeginChild("Spot Lights");

					{
						std::string id = light->GetId() + "###" + light->GetId() + "id";
						std::string id1 = ": Position###" + light->GetId() + "id1";
						std::string id2 = ": Position###" + light->GetId() + "id2";
						ImGui::Text(id.c_str());
						{
							glm::vec3 pos = light->GetPosition();
							if (ImGui::SliderFloat3(id1.c_str(), glm::value_ptr(pos), -100, 100)) {
								light->SetPosition(pos);
							}
							if (ImGui::InputFloat3(id2.c_str(), glm::value_ptr(pos))) {
								light->SetPosition(pos);
							}
						}

						{
							glm::vec3 color = light->GetColor() * glm::vec3(255);
							if (ImGui::ColorEdit3("Light Color", glm::value_ptr(color))) {
								light->SetColor(color / glm::vec3(255.0f));
							}
						}

						{
							if (ImGui::RadioButton("Is Static", light->GetStatic())) {
								light->SetStatic(!light->GetStatic());
							}
						}

						{
							float val = light->GetStrength();
							if (ImGui::DragFloat("Strength", &val, 1.0f, 0.0f, 100.0f)) {
								light->SetStrength(val);
							}
						}

						{
							float val = light->GetAffectiveDistance();

							if (ImGui::DragFloat("Affective Distance", &val, 1.0f, 0.0f, 100.0f)) {
								light->SetAffectiveDistance(val);
							}
						}

						{
							float val = light->GetAngle();

							if (ImGui::DragFloat("Angle", &val, 1.0f, 0.0f, 100.0f)) {
								light->SetAngle(val);
							}
						}

						{
							glm::vec3 direction = light->GetDirection();

							if (ImGui::InputFloat3("Direction ", glm::value_ptr(direction))) {
								light->SetPosition(direction);
							}
						}
					}

					ImGui::EndChild();
				}
			}
		}
		ImGui::End();
	}

	void OptionsManager::SetCurrent()
	{

	}
}
