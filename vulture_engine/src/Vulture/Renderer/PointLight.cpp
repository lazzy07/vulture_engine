#include "vulpch.h"
#include "PointLight.h"

Vulture::PointLight::PointLight(glm::vec3 position, glm::vec3 color, float strength, bool isStatic) : 
	Light(position, color, strength, isStatic)
{
}

Vulture::PointLight::~PointLight()
{
}
