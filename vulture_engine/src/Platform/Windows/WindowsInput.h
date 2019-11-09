#pragma once
#include "Vulture/Input.h"

namespace Vulture {
	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseYImpl() override;
		virtual float GetMouseXImpl() override;
	};
}