workspace "Crimson"
	startproject "Sandbox"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

buildoptions { "/utf-8" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include dirs relative to solution dir
IncludeDir = {}
IncludeDir["GLFW"] = "Crimson/vendor/GLFW/include"
IncludeDir["Glad"] = "Crimson/vendor/Glad/include"
IncludeDir["ImGui"] = "Crimson/vendor/imgui"
IncludeDir["Chroma"] = "Crimson/vendor/Chroma"
IncludeDir["Stb"] = "Crimson/vendor/stb"


group "Dependencies"
	include "Crimson/vendor/GLFW"
	include "Crimson/vendor/imgui"
	include "Crimson/vendor/Glad"
	include "Crimson/vendor/Chroma"
group ""


project "Crimson"
	location "Crimson"	
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cnpch.h"
	pchsource "Crimson/src/cnpch.cpp"

	files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/Events/**.h",
        "%{prj.name}/src/Events/**.cpp",
        "%{prj.name}/vendor/stb/**.cpp",
        "%{prj.name}/vendor/stb/**.h",
        "%{prj.name}/Platform/Windows/**.h",
        "%{prj.name}/Platform/Windows/**.cpp"
    }

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"Crimson/vendor/spdlog/include",
		"Crimson/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Chroma}",
		"%{IncludeDir.Stb}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"Chroma",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CN_PLATFORM_WINDOWS",
			"CN_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	
	filter "toolset:gcc or toolset:clang" -- For GCC and Clang
		buildoptions { "-msse", "-mavx" }  --  SSE and AVX support

	filter "toolset:msc"  -- For MSVC
		buildoptions { "/arch:SSE", "/arch:AVX" }  -- SSE and AVX support
	

	filter "configurations:Debug"
		defines {"CN_DEBUG", "CN_ENABLE_ASSERTS"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CN_DIST"
		runtime "Release"
		optimize "on"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }



	includedirs
	{
		"Crimson/vendor/spdlog/include",
		"Crimson/src",
		"Crimson/vendor",
		"Crimson/vendor/Chroma"
	}

	links
	{
		"Crimson"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CN_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines {"CN_DEBUG", "CN_ENABLE_ASSERTS"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CN_DIST"
		buildoptions "Release"
		optimize "on"
