#include "vulpch.h"
#include "DirectionalLight.h"

namespace Vulture {
	DirectionalLight::DirectionalLight(std::string id, glm::vec3 position, glm::vec3 color, float strength, float affectiveDistance, bool isStatic, glm::vec3 direction)
		: Light(id, position, color, strength, affectiveDistance, isStatic), m_Direction(direction) {

	}

	DirectionalLight::~DirectionalLight()
	{
	}
}