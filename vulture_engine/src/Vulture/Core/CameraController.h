#pragma once
#include "Vulture/Core/Core.h"
#include "Vulture/Renderer/PerspectiveCamera.h"
#include "Vulture/Renderer/OrthographicCamera.h"
#include "Vulture/Core/KeyCodes.h"

namespace Vulture {
	class CameraController {
	public:
		virtual void RunController(const VULTURE_KEY keyUp, const VULTURE_KEY keyDown, 
			const VULTURE_KEY keyLeft, const VULTURE_KEY keyRight, const float cameraSpeed = 0.05f) = 0;
		virtual Ref<Camera> GetCamera() = 0;
	};

	class FirstPersonController : public CameraController {
	public:
		FirstPersonController();
		virtual Ref<Camera> GetCamera() override { return m_Camera; };
		virtual void RunController(const VULTURE_KEY keyUp, const VULTURE_KEY keyDown, 
			const VULTURE_KEY keyLeft, const VULTURE_KEY keyRight, const float cameraSpeed = 0.05f) override;

	private:
		void OnChangeMouse();
		void OnChangeKeyboard(const VULTURE_KEY keyUp, const VULTURE_KEY keyDown, 
			const VULTURE_KEY keyLeft, const VULTURE_KEY keyRight, const float cameraSpeed);
	private:
		float m_MouseSensitivity = 0.2f;
		Ref<PerspectiveCamera> m_Camera;

		bool m_firstMouse = false;
		float m_lastX = 1280 / 2;
		float m_lastY = 720 / 2;
	};

	class Ortho2d : public CameraController {
	private:
		virtual void RunController(const VULTURE_KEY keyUp, const VULTURE_KEY keyDown, 
			const VULTURE_KEY keyLeft, const VULTURE_KEY keyRight, const float cameraSpeed = 0.05f) override;
	private:
		Ref<OrthographicCamera> m_Camera;
	};
}