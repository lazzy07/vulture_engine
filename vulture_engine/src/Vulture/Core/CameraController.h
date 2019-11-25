#pragma once
#include "Vulture/Core/Core.h"
#include "Vulture/Renderer/PerspectiveCamera.h"
#include "Vulture/Renderer/OrthographicCamera.h"

namespace Vulture {
	class CameraController {
	public:
		virtual void RunController() = 0;
		virtual Ref<Camera> GetCamera() = 0;
	};

	class FirstPersonController : public CameraController {
	public:
		FirstPersonController();
		virtual Ref<Camera> GetCamera() override { return m_Camera; };
		virtual void RunController() override;

	private:
		void OnChangeMouse();
	private:
		float m_MouseSensitivity = 0.1f;
		Ref<PerspectiveCamera> m_Camera;

		bool m_firstMouse = false;
		float m_lastX = 1280 / 2;
		float m_lastY = 720 / 2;
	};

	class Ortho2d : public CameraController {
	private:
		virtual void RunController() override;
	private:
		Ref<OrthographicCamera> m_Camera;
	};
}