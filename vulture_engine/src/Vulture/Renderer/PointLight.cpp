#include "vulpch.h"
#include "PointLight.h"

Vulture::PointLight::PointLight(std::string id, glm::vec3 position, glm::vec3 color, float strength, float affectiveDistance, bool isStatic) :
	Light(id, position, color, strength, affectiveDistance, isStatic)
{

}

Vulture::PointLight::~PointLight()
{
}

void Vulture::PointLight::SaveLightData(Configurations * cfg)
{
	cfg->SetString("lights", GetId(), "point");

	cfg->SetVec3(GetId(), "position", GetPosition());
	cfg->SetFloat(GetId(), "strength", GetStrength());
	cfg->SetVec3(GetId(), "color", GetColor());
	cfg->SetFloat(GetId(), "affectivedist", GetAffectiveDistance());
	cfg->SetFloat(GetId(), "active", GetIsActive());
	cfg->SetFloat(GetId(), "static", GetStatic());
}
