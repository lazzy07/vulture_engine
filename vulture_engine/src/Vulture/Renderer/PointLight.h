#pragma once
#include "Light.h"

namespace Vulture {
	class PointLight : public Light {
	public:
		PointLight(std::string id, glm::vec3 position = glm::vec3(0.0), glm::vec3 color = glm::vec3(1.0), float strength = 0.5f, float affectiveDistance = 10.0f, bool isStatic = true);
		~PointLight();
	};
}
