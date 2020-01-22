#pragma once
#include "Vulture/Core/Layer.h"

namespace Vulture {
	class MaterialManager : public Layer {
	public:
		MaterialManager();
		~MaterialManager();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
	};
}