#pragma once
#include "Vulture/Core/Layer.h"
#include "Vulture/Core/FileManager.h"

namespace Vulture {
	class MaterialManager : public Layer {
	public:
		MaterialManager();
		~MaterialManager();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void UpdateList();
		void AddMaterialToLevel();
	private:
		int m_Selected = -1;
		FileManager m_FileManager;
		char m_NewFile[1000] = "";
		std::vector<std::string> m_MaterialList;
	};
}