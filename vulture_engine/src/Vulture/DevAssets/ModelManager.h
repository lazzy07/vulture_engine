#pragma once
#include "Vulture/Core/Layer.h"
#include "Vulture/Core/FileManager.h"

namespace Vulture {
	class ModelManager : public Layer {
	public:
		ModelManager();
		~ModelManager();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void UpdateModelList();
		void AddModelToLevel();
	private:
		int m_Selected = -1;
		FileManager m_FileManager;
		std::vector<std::string> m_ModelList;
	};
}