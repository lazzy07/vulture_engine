#include "vulpch.h"
#include "TextureManager.h"

#include "imgui.h"
#include "Vulture/Core/Application.h"

namespace Vulture {
	TextureManager::TextureManager() : Layer("TextureManager")
	{
	}
	TextureManager::~TextureManager()
	{
	}
	void TextureManager::OnAttach()
	{
	}
	void TextureManager::OnDetach()
	{
	}
	void TextureManager::OnImGuiRender()
	{
		UpdateList();
		ImGui::Begin("TextureManager");
		{
			ImGui::ListBoxHeader("###TextureList");
			{
				for (int i = 0; i < m_TextureList.size(); i++) {
					if (ImGui::Selectable(FileManager::GetFileName(m_TextureList[i]).c_str(), m_Selected == i)) {
						m_Selected = i;
					}
				}
			}
			ImGui::ListBoxFooter();
			{
				if (ImGui::Button("Add to Level###TextureAddToLevel")) {
					AddShaderToLevel();
				}
				ImGui::SameLine();
				if (ImGui::Button("Update List###UpdateTextureList")) {
					UpdateList();
				}
				ImGui::SameLine();
			}
		}
		ImGui::End();
	}
	void TextureManager::UpdateList()
	{
		m_TextureList.clear();
		m_FileManager.GetFileList("./assets/textures", "png", &m_TextureList);
		m_FileManager.GetFileList("./assets/textures", "jpg", &m_TextureList);
		m_FileManager.GetFileList("./assets/textures", "jpeg", &m_TextureList);
		m_FileManager.GetFileList("./assets/textures", "hdr", &m_TextureList);
	}
	void TextureManager::AddShaderToLevel()
	{
		if (m_Selected > 0 && m_Selected < m_TextureList.size()) {
			Application::Get().GetCurrentLevel()->AddNewTexture(m_TextureList[m_Selected]);
		}
		else {
			VUL_CORE_WARN("Shader is not valid or a shader wasn't selected");
		}
	}
}