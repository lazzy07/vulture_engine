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

include "vulture_engine/vendor/GLFW"

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
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "10.0.17763.0"
		defines
		{
			"VUL_PLATFORM_WINDOWS",
			"VUL_BUILD_DLL"
		}
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/sandbox")
		}

	filter "configurations:Debug"
		defines "VUL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VUL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VUL_DIST"
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
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VUL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VUL_DIST"
		runtime "Release"
		optimize "on"