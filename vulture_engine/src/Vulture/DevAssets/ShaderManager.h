#pragma once
#include "Vulture/Core/Layer.h"

namespace Vulture {
	class ShaderManager : public Layer {
	public:	
		ShaderManager();
		~ShaderManager();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
	};
}