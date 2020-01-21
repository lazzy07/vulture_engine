#include "vulpch.h"
#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Vulture {
	PerspectiveCamera::PerspectiveCamera(int screenHeight, int screenWidth, float angle, float nearPlane, float farPlane, glm::vec3 position, const float yaw , const float pitch) :
		m_ViewMatrix(1.0f),
		m_ProjectionMatrix(glm::perspective(glm::radians(angle), (float)screenWidth / (float)screenHeight, nearPlane, farPlane)),
		m_Position(position)
	{
		m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Yaw = yaw;
		m_Pitch = pitch;
		RecalculateMatrices();
	}

	void PerspectiveCamera::UpdateViewMatrix(int screenHeight, int screenWidth, float angle, float nearPlane, float farPlane)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(angle), (float)screenWidth / (float)screenHeight, nearPlane, farPlane);
	}

	void PerspectiveCamera::RecalculateMatrices()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + front, m_Up);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}