#include "vulpch.h"
#include "Light.h"

namespace Vulture {
	Light::Light(std::string id, glm::vec3 position, glm::vec3 color, float strength, float affectiveDistance, bool isStatic) 
		: m_Position(position), m_Color(color), m_Strength(strength), m_AffectiveDistance(affectiveDistance) ,m_IsStatic(isStatic) {

	}

	Light::~Light() {

	}

	bool Light::IsLightAffected(glm::vec3 modelPosition)
	{
		glm::vec3 pos = GetPosition();
		float range = GetAffectiveDistance();
		if (modelPosition.x < pos.x + range && modelPosition.x > pos.x - range) {
			if (modelPosition.y < pos.y + range && modelPosition.y > pos.y - range) {
				if (modelPosition.z < pos.z + range && modelPosition.z > pos.z - range) {
					return true;
				}
			}
		}
		return false;
	}
}