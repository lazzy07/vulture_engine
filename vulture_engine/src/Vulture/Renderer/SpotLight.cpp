#include "SpotLight.h"

namespace Vulture {
	SpotLight::SpotLight(glm::vec3 position, glm::vec3 color, float strength, bool isStatic, float angle) 
		: Light(position, color, strength, isStatic), m_Angle(angle)
	{
	}
	SpotLight::~SpotLight()
	{
	}
}