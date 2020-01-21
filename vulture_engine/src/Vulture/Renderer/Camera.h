#pragma once
#include <glm/glm.hpp>

namespace Vulture {
	class Camera {
	public:
		virtual void UpdateViewMatrix(int Screenheight = 720, int screenWidth = 1280, float angle = 54.0f, float nearPlane = 0.1f, float farPlane = 100.0f) = 0;
		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
	};
}