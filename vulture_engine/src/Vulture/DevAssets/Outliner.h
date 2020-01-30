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
		static inline std::string GetSelectedMaterial() { return m_SelectedMaterial; };
		static inline std::string GetSelectedShader() { return m_SelectedShader; };
		static inline std::string GetSelectedTexture() { return m_SelectedTexture; };
		static inline std::string GetSelectedLight() { return m_SelectedLight; };
		static inline std::string GetSelectedLightInstance() { return m_SelectedLightInstance; };

		static inline void ResetSelected() { m_SelectedObject = m_SelectedInstance 
			= m_SelectedMaterial = m_SelectedShader = m_SelectedTexture = m_SelectedLight = m_SelectedLightInstance = ""; };
	private:
		std::unordered_map<std::string, std::vector<Ref<LevelModelData>>> m_Instances;

		static std::string m_SelectedObject;
		static std::string m_SelectedInstance;
		static std::string m_SelectedMaterial;
		static std::string m_SelectedShader;
		static std::string m_SelectedTexture;
		static std::string m_SelectedLight;
		static std::string m_SelectedLightInstance;
	};
}