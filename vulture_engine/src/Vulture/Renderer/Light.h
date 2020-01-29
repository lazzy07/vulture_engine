#pragma once
#include <glm/glm.hpp>

namespace Vulture {
	enum class LightTypes {
		POINT_LIGHT,
		DIRECTIONAL_LIGHT,
		SPOT_LIGHT
	};

	class Light {
	public:
		Light(std::string id, glm::vec3 position, glm::vec3 color, float strength, float affectiveDistance, bool isStatic);
		~Light();

		bool IsLightAffected(glm::vec3 modelPosition);

		inline const glm::vec3 GetPosition() const { return m_Position; };
		inline const glm::vec3 GetColor() const { return m_Color; };
		inline const float GetStrength() const { return m_Strength; };
		inline const bool GetStatic() const { return m_IsStatic; };
		inline const bool GetIsActive() const { return m_IsActive; };
		inline const float GetAffectiveDistance() const { return m_AffectiveDistance; };

		inline const std::string GetId() const { return m_Id; };

		inline void SetId(std::string id) { m_Id = id; };

		inline void SetPosition(glm::vec3 position) { m_Position = position; };
		inline void SetColor(glm::vec3 color) { m_Color = color; };
		inline void SetStrength(float strength) { m_Strength = strength; };
		inline void SetStatic(bool isStatic) { m_IsStatic = isStatic; };
		inline void SetActive(bool isActive) { m_IsActive = isActive; };
		inline void SetAffectiveDistance(float affectiveDist) { m_AffectiveDistance = affectiveDist; }
	private:
		std::string m_Id;

		bool m_IsActive;
		bool m_IsStatic;
		
		LightTypes m_LightType;
		glm::vec3 m_Position;
		glm::vec3 m_Color;
		float m_Strength;
		float m_AffectiveDistance;
	};
}