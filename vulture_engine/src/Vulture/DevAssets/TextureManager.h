#pragma once
#include "Vulture/Core/Layer.h"


namespace Vulture {
	class TextureManager : public Layer {
	public:
		TextureManager();
		~TextureManager();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
	};
}