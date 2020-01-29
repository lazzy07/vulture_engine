#pragma once
#include "Vulture/Core/Configurations.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

namespace Vulture {
	class LightsLibrary {
	public:
		void AddNewLight(LightTypes lightType);
		void GetLight(LightTypes lightType, int index);
		
		inline std::vector<PointLight>* GetPointLights() { return &m_PointLights; };
		inline std::vector<DirectionalLight>* GetDirectionalLights() { return &m_DirectionalLights; }
		inline std::vector<SpotLight>* GetSpotLights() { return &m_SpotLights; };

		void UpdateLights();
		void LoadLights();
		
		inline std::string GetConfigBuffer() { return m_Configurations.GetConfigBuffer(); };
	private:
		Configurations m_Configurations;

		std::vector<PointLight> m_PointLights;
		std::vector<DirectionalLight> m_DirectionalLights;
		std::vector<SpotLight> m_SpotLights;
	};
}