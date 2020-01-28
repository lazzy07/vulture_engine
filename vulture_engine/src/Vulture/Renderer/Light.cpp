#include "vulpch.h"
#include "Light.h"

namespace Vulture {
	Light::Light(glm::vec3 position, glm::vec3 color, float strength, bool isStatic) : m_Position(position), m_Color(color), m_Strength(strength), m_IsStatic(isStatic) {

	}

	Light::~Light() {

	}
}