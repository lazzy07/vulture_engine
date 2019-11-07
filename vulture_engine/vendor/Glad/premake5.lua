project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}
	
	filter "system:windows"
		systemversion "10.0.17763.0"
		staticruntime "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"
