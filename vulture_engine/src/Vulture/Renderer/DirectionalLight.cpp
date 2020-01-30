#include "vulpch.h"
#include "DirectionalLight.h"

namespace Vulture {
	DirectionalLight::DirectionalLight(std::string id, glm::vec3 position, glm::vec3 color, float strength, float affectiveDistance, bool isStatic, glm::vec3 direction)
		: Light(id, position, color, strength, affectiveDistance, isStatic), m_Direction(direction) {
		SetType(LightTypes::DIRECTIONAL_LIGHT);
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::SaveLightData(Configurations * cfg)
	{
		cfg->SetString("lights", GetId(), "directional");

		cfg->SetVec3(GetId(), "position", GetPosition());
		cfg->SetFloat(GetId(), "strength", GetStrength());
		cfg->SetVec3(GetId(), "color", GetColor());
		cfg->SetFloat(GetId(), "affectivedist", GetAffectiveDistance());
		cfg->SetFloat(GetId(), "active", GetIsActive());
		cfg->SetFloat(GetId(), "static", GetStatic());

		cfg->SetVec3(GetId(), "direction", m_Direction);
	}
}