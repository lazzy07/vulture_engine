#pragma once

#include "Vulture/Core/Layer.h"
#include "Vulture/Core/Level.h"

namespace Vulture {
	class OptionsManager : public Layer {
	public:
		OptionsManager();
		~OptionsManager();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

	private:
		void SetCurrent();
	private:
		Ref<LevelModelData> m_CurrentInstance;
	};
}

