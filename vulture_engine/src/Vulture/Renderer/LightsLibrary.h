#pragma once
#include "Vulture/Core/Configurations.h"

#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

#include "ModelLibrary.h"

namespace Vulture {
	class LightsLibrary {
	public:
		LightsLibrary(Ref<ModelLibrary> modelLibrary);
		~LightsLibrary();

		void AddNewLight(LightTypes lightType);

		Ref<DirectionalLight> GetDirectionalLight(int index);
		Ref<SpotLight> GetSpotLight(int index);
		Ref<PointLight> GetPointLight(int index);

		inline std::vector<Ref<PointLight>>* GetPointLights() { return &m_PointLights; };
		inline std::vector<Ref<DirectionalLight>>* GetDirectionalLights() { return &m_DirectionalLights; }
		inline std::vector<Ref<SpotLight>>* GetSpotLights() { return &m_SpotLights; };

		inline glm::vec3 GetAmbientLight() const { return m_AmbientColor; };
		
		void ChangeAmbientLight(glm::vec3 color);

		void UpdateLights();
		void LoadLights(const char* buffer);
		
		std::string GetConfigBuffer();
	private:
		inline void SetAmbientLight(glm::vec3 color) { m_AmbientColor = color; };
		Configurations m_Config;

		Ref<ModelLibrary> m_ModelLibrary;

		std::vector<Ref<PointLight>> m_PointLights;
		std::vector<Ref<DirectionalLight>> m_DirectionalLights;
		std::vector<Ref<SpotLight>> m_SpotLights;

		glm::vec3 m_AmbientColor;
	};
}