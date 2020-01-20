#pragma once

#include "Vulture/Core/Layer.h"

namespace Vulture {
	class InstanceManager : public Layer {
	public:
		InstanceManager();
		~InstanceManager();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
	private:
		std::string m_CurrentInstance;
	};
}

