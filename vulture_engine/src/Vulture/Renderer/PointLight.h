#pragma once
#include "Light.h"

namespace Vulture {
	class PointLight : public Light {
	public:
		PointLight(glm::vec3 position = glm::vec3(0.0), glm::vec3 color = glm::vec3(1.0), float strength = 0.5f, bool isStatic = true);
		~PointLight();
	};
}
