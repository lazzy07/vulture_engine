#pragma once
#include <glm/glm.hpp>
#include "Camera.h"

namespace Vulture {
	class OrthographicCamera: public Camera {
	public:
		OrthographicCamera(float left = -1.6f, float right = 1.6f, float bottom = -0.9f, float top = 0.9f);

		const glm::vec3& GetPosition() const { return m_Position; };
		const float GetRotation() const { return m_Rotation; };

		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); };
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); };

		virtual const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; };
		virtual const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; };
		virtual const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; } ;
		virtual void UpdateViewMatrix(int Screenheight, int screenWidth, float angle, float nearPlane, float farPlane) {};
	private:
		void RecalculateViewMatrix();

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
		float m_Rotation = 0.0f;
	};
}