workspace "vulture_engine"
	architecture "x64"
	startproject "sandbox"

	defines
	{
		"VUL_USE_GPU"
	}

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
IncludeDir["glm"] = "vulture_engine/vendor/glm"
IncludeDir["stb_image"] = "vulture_engine/vendor/stb_image"

include "vulture_engine/vendor/GLFW"
include "vulture_engine/vendor/Glad"
include "vulture_engine/vendor/ImGui"


project "vulture_engine"
	location "vulture_engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "vulpch.h"
	pchsource "vulture_engine/src/vulpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "10.0.17763.0"
		defines
		{
			"VUL_PLATFORM_WINDOWS",
			"VUL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
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
	cppdialect "C++17"
	staticruntime "on"

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
		"vulture_engine/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"vulture_engine"
	}

	filter "system:windows"
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