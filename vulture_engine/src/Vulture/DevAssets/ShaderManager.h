#pragma once
#include "Vulture/Core/Layer.h"
#include "Vulture/Core/FileManager.h"

namespace Vulture {
	class ShaderManager : public Layer {
	public:	
		ShaderManager();
		~ShaderManager();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void UpdateList();
		void AddShaderToLevel();
	private:
		int m_Selected = -1;
		FileManager m_FileManager;
		std::vector<std::string> m_ShaderList;
	};
}