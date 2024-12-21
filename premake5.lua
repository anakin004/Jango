workspace "Crimson"
	
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

include "Crimson/vendor/GLFW"
include "Crimson/vendor/Glad"


project "Crimson"
	location "Crimson"	
	kind "SharedLib"
	language "C++"

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
        "%{prj.name}/Platform/Windows/**.h",
        "%{prj.name}/Platform/Windows/**.cpp"
    }

	includedirs
	{
		"Crimson/vendor/spdlog/include",
		"Crimson/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CN_PLATFORM_WINDOWS",
			"CN_BUILD_DLL"
		}

		postbuildcommands
		{
			"{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
		}

	filter "configurations:Debug"
		defines {"CN_DEBUG", "CN_ENABLE_ASSERTS"}
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "CN_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "CN_DIST"
		buildoptions "/MD"
		optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Crimson/src"
	}

	links
	{
		"Crimson"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines {"CN_DEBUG", "CN_ENABLE_ASSERTS"}
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "CN_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "CN_DIST"
		buildoptions "/MD"
		optimize "On"
