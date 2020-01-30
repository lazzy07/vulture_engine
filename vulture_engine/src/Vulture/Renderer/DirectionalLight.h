#pragma once
#include "Light.h"
#include "Vulture/Core/Configurations.h"

namespace Vulture {
	class DirectionalLight : public Light {
	public:
		DirectionalLight(std::string id, glm::vec3 position = glm::vec3(0.0), glm::vec3 color = glm::vec3(1.0), float strength = 0.5f, float affectiveDistance = 10.0f, bool isStatic = true, glm::vec3 direction = glm::vec3(0.0f));
		~DirectionalLight();

		virtual void SaveLightData(Configurations* cfg) override;

		inline glm::vec3 GetDirection() const { return m_Direction; };

		inline void SetDirection(glm::vec3 direction) { m_Direction = direction; };
	private:
		glm::vec3 m_Direction;
	};
}