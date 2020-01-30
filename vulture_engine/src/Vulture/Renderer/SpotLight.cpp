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
	void SpotLight::SaveLightData(Configurations * cfg)
	{
		cfg->SetString("lights", GetId(), "spot");

		cfg->SetVec3(GetId(), "position", GetPosition());
		cfg->SetFloat(GetId(), "strength", GetStrength());
		cfg->SetVec3(GetId(), "color", GetColor());
		cfg->SetFloat(GetId(), "affectivedist", GetAffectiveDistance());
		cfg->SetFloat(GetId(), "active", GetIsActive());
		cfg->SetFloat(GetId(), "static", GetStatic());
		
		cfg->SetFloat(GetId(), "angle", m_Angle);
		cfg->SetVec3(GetId(), "direction", m_Direction);
	}
}