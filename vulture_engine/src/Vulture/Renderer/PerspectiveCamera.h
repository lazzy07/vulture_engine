#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

namespace Vulture {
	class PerspectiveCamera : public Camera {
	public:
		PerspectiveCamera(int Screenheight = 720, int screenWidth = 1280, float angle=54.0f, float nearPlane = 0.1f, float farPlane = 100.0f, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), const float yaw = -90.0f, const float pitch = 0.0f);
		~PerspectiveCamera() = default;

		inline void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateMatrices(); };
		
		inline void SetYaw(float yaw) { m_Yaw = yaw; RecalculateMatrices(); };
		inline void SetPitch(float pitch) { m_Pitch = pitch; RecalculateMatrices(); };

		virtual void UpdateViewMatrix(int Screenheight = 720, int screenWidth = 1280, float angle = 54.0f, float nearPlane = 0.1f, float farPlane = 100.0f);

		const glm::vec3& GetPosition() const { return m_Position; };

		void SetFront(glm::vec3 front) { m_Front = front; };
		void SetUp(glm::vec3 up) { m_Up = up; };
		void SetRight(glm::vec3 right) { m_Right = right; };
		
		const float GetYaw() { return m_Yaw; };
		const float GetPitch() { return m_Pitch; };

		const glm::vec3& GetFront() { return m_Front; };
		const glm::vec3& GetUp() { return m_Up; };
		const glm::vec3& GetRight() { return m_Right; };



		virtual const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; };
		virtual const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; };
		virtual const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; };
	private:
		void RecalculateMatrices();
	private:
		glm::vec3 m_Position;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::mat4 m_ModelMatrix;

		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;

		float m_Yaw;
		float m_Pitch;

		float m_MovementSpeed = 2.5f;
		float m_TurnSensivity = 0.1f;
		float m_Zoom = 1.0f;
	};
}
