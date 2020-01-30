#pragma once
#include "Light.h"

namespace Vulture {
	class SpotLight : public Light {
	public:
		SpotLight(std::string id, glm::vec3 position = glm::vec3(0.0), glm::vec3 color = glm::vec3(1.0), float strength = 0.5f, float affectiveDistance = 10.0f, bool isStatic = true, glm::vec3 direction = glm::vec3(0.0f),float angle = 45.0f);
		~SpotLight();

		virtual void SaveLightData(Configurations* cfg) override;

		inline const float GetAngle() const { return m_Angle; };
		inline const glm::vec3 GetDirection() const { return m_Direction; };

		inline void SetAngle(float angle) { m_Angle = angle; };
		inline void SetDirection(glm::vec3 direction) { m_Direction = direction; };
	private:
		float m_Angle;
		glm::vec3 m_Direction;
	};
}
