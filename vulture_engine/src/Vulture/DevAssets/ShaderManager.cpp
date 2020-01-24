#include "vulpch.h"
#include "ShaderManager.h"

#include "imgui.h"
#include "Vulture/Core/Application.h"

namespace Vulture{
	ShaderManager::ShaderManager() : Layer("ShaderManager")
	{
	}

	ShaderManager::~ShaderManager()
	{
	}
	void ShaderManager::OnAttach()
	{
	}

	void ShaderManager::OnDetach()
	{
	}

	void ShaderManager::OnImGuiRender()
	{
		UpdateList();
		ImGui::Begin("ShaderManager");
		{
			ImGui::ListBoxHeader("###ShaderList");
			{
				for (int i = 0; i < m_ShaderList.size(); i++) {
					if (ImGui::Selectable(FileManager::GetFileName(m_ShaderList[i]).c_str(), m_Selected == i)) {
						m_Selected = i;
					}
				}
			}
			ImGui::ListBoxFooter();
			{
				if (ImGui::Button("Add to Level###ShaderAddToLevel")) {
					AddShaderToLevel();
				}
				ImGui::SameLine();
				if (ImGui::Button("Update List###UpdateShaderList")) {
					UpdateList();
				}
				ImGui::SameLine();
			}
		}
		ImGui::End();
	}
	void ShaderManager::UpdateList()
	{
		m_ShaderList.clear();
		m_FileManager.GetFileList("./assets/shaders", "glsl", &m_ShaderList);
	}

	void ShaderManager::AddShaderToLevel()
	{
		if (m_Selected >= 0 && m_Selected < m_ShaderList.size()) {
			Application::Get().GetCurrentLevel()->AddNewShader(FileManager::GetFileName(m_ShaderList[m_Selected]));
		}
		else {
			VUL_CORE_WARN("Shader is not valid or a shader wasn't selected");
		}
	}
}
