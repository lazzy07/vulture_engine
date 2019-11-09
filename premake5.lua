workspace "vulture_engine"
	architecture "x64"
	startproject "sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags 
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.system}/%{cfg.buildcfg}_%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "vulture_engine/vendor/GLFW/include"
IncludeDir["Glad"] = "vulture_engine/vendor/Glad/include"
IncludeDir["ImGui"] = "vulture_engine/vendor/ImGui"

include "vulture_engine/vendor/GLFW"
include "vulture_engine/vendor/Glad"
include "vulture_engine/vendor/ImGui"


project "vulture_engine"
	location "vulture_engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "vulpch.h"
	pchsource "vulture_engine/src/vulpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "10.0.17763.0"
		defines
		{
			"VUL_PLATFORM_WINDOWS",
			"VUL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/sandbox")
		}

	filter "configurations:Debug"
		defines "VUL_DEBUG"
		buildoptions "/MDd"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VUL_RELEASE"
		buildoptions "/MD"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VUL_DIST"
		buildoptions "/MD"
		runtime "Release"
		optimize "on"

project "sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"vulture_engine/vendor/spdlog/include",
		"vulture_engine/src"
	}

	links
	{
		"vulture_engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "10.0.17763.0"
		defines
		{
			"VUL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VUL_DEBUG"
		buildoptions "/MDd"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VUL_RELEASE"
		buildoptions "/MD"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VUL_DIST"
		buildoptions "/MD"
		runtime "Release"
		optimize "on"