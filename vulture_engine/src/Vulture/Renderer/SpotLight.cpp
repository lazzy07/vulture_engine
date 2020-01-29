#include "vulpch.h"
#include "SpotLight.h"

namespace Vulture {
	SpotLight::SpotLight(std::string id, glm::vec3 position, glm::vec3 color, float strength, float affectiveDistance, bool isStatic, glm::vec3 direction, float angle) 
		: Light(id, position, color, strength, affectiveDistance, isStatic), m_Angle(angle), m_Direction(direction)
	{
	}

	SpotLight::~SpotLight()
	{
	}
}