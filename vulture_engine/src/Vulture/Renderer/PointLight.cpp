#include "vulpch.h"
#include "PointLight.h"

Vulture::PointLight::PointLight(std::string id, glm::vec3 position, glm::vec3 color, float strength, float affectiveDistance, bool isStatic) :
	Light(id, position, color, strength, affectiveDistance, isStatic)
{

}

Vulture::PointLight::~PointLight()
{

}
