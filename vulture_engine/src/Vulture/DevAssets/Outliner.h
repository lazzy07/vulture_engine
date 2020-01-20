#pragma once
#include "Vulture/Core/Layer.h"
#include "Vulture/Core/Level.h"

namespace Vulture {
	class Outliner : public Layer {
	public:
		Outliner();
		~Outliner();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void UpdateOutliner();

		inline std::string GetSelectedInstance() const { return m_SelectedInstance; };

	private:
		std::unordered_map<std::string, std::vector<Ref<LevelModelData>>> m_Instances;
		std::string m_SelectedInstance = "";
	};
}