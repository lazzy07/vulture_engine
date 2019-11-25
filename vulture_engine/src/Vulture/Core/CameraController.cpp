#include "vulpch.h"
#include "CameraController.h"
#include "Vulture/Core/Input.h"

namespace Vulture {
	FirstPersonController::FirstPersonController(): m_Camera(new PerspectiveCamera())
	{

	}

	void FirstPersonController::RunController()
	{
		OnChangeMouse();
	}

	void FirstPersonController::OnChangeMouse()
	{
		float xpos = Input::GetMouseX();
		float ypos = Input::GetMouseY();

		if (m_firstMouse)
		{
			m_lastX = xpos;
			m_lastY = ypos;
			m_firstMouse = false;
		}

		float xoffset = xpos - m_lastX;
		float yoffset = m_lastY - ypos;

		m_lastX = xpos;
		m_lastY = ypos;

		xoffset *= m_MouseSensitivity;
		yoffset *= m_MouseSensitivity;

		float yaw = m_Camera->GetYaw();
		float pitch = m_Camera->GetPitch();

		yaw += xoffset;
		pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		m_Camera->SetPitch(pitch);
		m_Camera->SetYaw(yaw);
	}

	void Ortho2d::RunController()
	{

	}
}
