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


		static inline std::string GetSelectedInstance() { return m_SelectedInstance; };
		static inline std::string GetSelectedObject() { return m_SelectedObject; };

		static inline void ResetSelected() { m_SelectedObject = m_SelectedInstance = ""; };
	private:
		std::unordered_map<std::string, std::vector<Ref<LevelModelData>>> m_Instances;
		static std::string m_SelectedInstance;
		static std::string m_SelectedObject;
	};
}