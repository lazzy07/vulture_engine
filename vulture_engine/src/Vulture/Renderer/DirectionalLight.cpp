#include "vulpch.h"
#include "DirectionalLight.h"

namespace Vulture {
	DirectionalLight::DirectionalLight(glm::vec3 position, glm::vec3 color, float strength, bool isStatic, glm::vec3 direction)
		: Light(position, color, strength, isStatic), m_Direction(direction) {

	}

	DirectionalLight::~DirectionalLight()
	{
	}
}