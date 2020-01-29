#include "vulpch.h"
#include "LightsLibrary.h"

namespace Vulture {
	void LightsLibrary::AddNewLight(LightTypes lightType)
	{
		switch (lightType) {
		case LightTypes::DIRECTIONAL_LIGHT:
			break;
		case LightTypes::POINT_LIGHT:
			break;
		case LightTypes::SPOT_LIGHT:
			break;
		default:
			VUL_CORE_ASSERT(false, "Unrecognized lighttype in addnewlight");
		}
	}

	void LightsLibrary::UpdateLights()
	{

	}
	void LightsLibrary::LoadLights()
	{
	}
	std::string LightsLibrary::GetConfigBuffer()
	{
		return std::string();
	}
}