#include "vulpch.h"
#include "CameraController.h"
#include "Vulture/Core/Input.h"

namespace Vulture {
	FirstPersonController::FirstPersonController(): m_Camera(new PerspectiveCamera())
	{

	}

	void FirstPersonController::RunController(const VULTURE_KEY keyUp, const VULTURE_KEY keyDown, 
		const VULTURE_KEY keyLeft, const VULTURE_KEY keyRight, const float cameraSpeed)
	{
		OnChangeMouse();
		OnChangeKeyboard(keyUp, keyDown, keyLeft, keyRight, cameraSpeed);
	}

	void FirstPersonController::OnChangeKeyboard(const VULTURE_KEY keyUp, const VULTURE_KEY keyDown, 
		const VULTURE_KEY keyLeft, const VULTURE_KEY keyRight, const float cameraSpeed)
	{
		glm::vec3 cameraPos = m_Camera->GetPosition();

		if (Input::IsKeyPressed(keyUp)) {
			cameraPos += cameraSpeed * m_Camera->GetFront();
		}
		
		if(Input::IsKeyPressed(keyDown)){
			cameraPos -= cameraSpeed * m_Camera->GetFront();
		};

		if (Input::IsKeyPressed(keyLeft)) {
			cameraPos -= glm::normalize(glm::cross(m_Camera->GetFront(), m_Camera->GetUp())) * cameraSpeed;
		}

		if (Input::IsKeyPressed(keyRight)) {
			cameraPos += glm::normalize(glm::cross(m_Camera->GetFront(), m_Camera->GetUp())) * cameraSpeed;
		}

		m_Camera->SetPosition(cameraPos);
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

		m_Camera->SetPitch(pitch);
		m_Camera->SetYaw(yaw);

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		m_Camera->SetFront(glm::normalize(front));
	}

	void Ortho2d::RunController(const VULTURE_KEY keyUp, const VULTURE_KEY keyDown, 
		const VULTURE_KEY keyLeft, const VULTURE_KEY keyRight, const float cameraSpeed)
	{

	}
}
