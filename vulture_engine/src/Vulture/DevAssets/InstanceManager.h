#pragma once

#include "Vulture/Core/Layer.h"
#include "Vulture/Core/Level.h"

namespace Vulture {
	class InstanceManager : public Layer {
	public:
		InstanceManager();
		~InstanceManager();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

	private:
		void SetCurrentInstance();
	private:
		Ref<LevelModelData> m_CurrentInstance;
	};
}

