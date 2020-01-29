#pragma once
#include "Light.h"

namespace Vulture {
	class SpotLight : public Light {
	public:
		SpotLight(std::string id, glm::vec3 position = glm::vec3(0.0), glm::vec3 color = glm::vec3(1.0), float strength = 0.5f, float affectiveDistance = 10.0f, bool isStatic = true, glm::vec3 direction = glm::vec3(0.0f),float angle = 45.0f);
		~SpotLight();
	private:
		float m_Angle;
		glm::vec3 m_Direction;
	};
}
