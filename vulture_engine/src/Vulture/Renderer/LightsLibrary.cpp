#include "vulpch.h"
#include "LightsLibrary.h"
#include "Vulture/Core/IdGenerator.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Vulture {
	LightsLibrary::LightsLibrary(Ref<ModelLibrary> modelLibrary) : m_ModelLibrary(modelLibrary)
	{

	}

	LightsLibrary::~LightsLibrary()
	{

	}

	void LightsLibrary::AddNewLight(LightTypes lightType)
	{
		std::string id = IdGenerator::GenerateId();
		if (lightType == LightTypes::DIRECTIONAL_LIGHT) {
			Ref<DirectionalLight> light;
			light.reset(new DirectionalLight(id, glm::vec3(0.0f), glm::vec3(0.0f), 0.5f, 10.0f, true, glm::vec3(0.0f)));
		}
		else if (lightType == LightTypes::POINT_LIGHT) {
			Ref<PointLight> light;
			light.reset(new PointLight(id, glm::vec3(0.0f), glm::vec3(0.0f), 0.5f, 10.0f, true));
		}
		else if (lightType == LightTypes::SPOT_LIGHT) {
			Ref<SpotLight> light;
			light.reset(new SpotLight(id, glm::vec3(0.0f), glm::vec3(0.0f), 0.5f, 10.0f, true, glm::vec3(0.0f), 45.0f));
		}
		else {
			VUL_CORE_ASSERT(false, "Unknown light type in addNewLight");
		}
	}

	Ref<DirectionalLight> LightsLibrary::GetDirectionalLight(int index)
	{
		return m_DirectionalLights[index];
	}

	Ref<SpotLight> LightsLibrary::GetSpotLight(int index)
	{
		return m_SpotLights[index];
	}

	Ref<PointLight> LightsLibrary::GetPointLight(int index)
	{
		return m_PointLights[index];
	}

	void LightsLibrary::ChangeAmbientLight(glm::vec3 color)
	{
		SetAmbientLight(color);
	}

	void LightsLibrary::UpdateLights()
	{

	}

	void LightsLibrary::LoadLights(const char* buffer)
	{
		m_Config.LoadConfigBuffer(buffer);

		std::unordered_map<std::string, std::string> config;

		m_Config.GetAll("lights", &config);

		for (auto ele : config) {
			std::string id = ele.first;
			if (ele.second == "directional") {
				Ref<DirectionalLight> dir;
				dir.reset(new DirectionalLight(ele.first));
				

				dir->SetPosition(m_Config.GetVec3(id, "position"));
				dir->SetStrength(m_Config.GetFloat(id, "strength"));
				dir->SetColor(m_Config.GetVec3(id, "color"));
				dir->SetAffectiveDistance(m_Config.GetFloat(id, "affectivedist"));
				dir->SetActive(m_Config.GetFloat(id, "active"));
				dir->SetStatic(m_Config.GetFloat(id, "static"));

				dir->SetDirection(m_Config.GetVec3(id, "direction"));

				m_DirectionalLights.push_back(dir);
			}
			else if (ele.second == "spot") {
				Ref<SpotLight> spot;
				spot.reset(new SpotLight(ele.first));

				spot->SetPosition(m_Config.GetVec3(id, "position"));
				spot->SetStrength(m_Config.GetFloat(id, "strength"));
				spot->SetColor(m_Config.GetVec3(id, "color"));
				spot->SetAffectiveDistance(m_Config.GetFloat(id, "affectivedist"));
				spot->SetActive(m_Config.GetFloat(id, "active"));
				spot->SetStatic(m_Config.GetFloat(id, "static"));

				spot->SetAngle(m_Config.GetFloat(id, "angle"));
				spot->SetDirection(m_Config.GetVec3(id, "direction"));

				m_SpotLights.push_back(spot);
			}
			else if (ele.second == "point") {
				Ref<PointLight> point;
				point.reset(new PointLight(ele.first));
				
				point->SetPosition(m_Config.GetVec3(id, "position"));
				point->SetStrength(m_Config.GetFloat(id, "strength"));
				point->SetColor(m_Config.GetVec3(id, "color"));
				point->SetAffectiveDistance(m_Config.GetFloat(id, "affectivedist"));
				point->SetActive(m_Config.GetFloat(id, "active"));
				point->SetStatic(m_Config.GetFloat(id, "static"));
				
				m_PointLights.push_back(point);
			}
			else {
				VUL_CORE_ASSERT(false, "Light type not recognized");
			}
		}
	}

	std::string LightsLibrary::GetConfigBuffer()
	{
		for (auto ele : m_DirectionalLights) {
			ele->SaveLightData(&m_Config);
		}

		for (auto ele : m_PointLights) {
			ele->SaveLightData(&m_Config);
		}

		for (auto ele : m_SpotLights) {
			ele->SaveLightData(&m_Config);
		}

		return m_Config.GetConfigBuffer();
	}
}