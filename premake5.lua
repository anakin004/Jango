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
IncludeDir["glm"] = "Crimson/vendor/glm"
IncludeDir["Stb"] = "Crimson/vendor/stb"
IncludeDir["entt"] = "Crimson/vendor/entt"
IncludeDir["curl"] = "Crimson/vendor/Curl/include"
IncludeDir["json"]= "Crimson/vendor/jsoncpp"
IncludeDir["assimp"]= "Crimson/vendor/assimp/include"
IncludeDir["Physx"]= "Crimson/vendor/physx_x64-windows/include"
IncludeDir["yaml_cpp"] = "Crimson/vendor/yaml_cpp/include"
IncludeDir["oidn"] = "Crimson/vendor/oidn/include"
IncludeDir["ImGuizmo"] = "Crimson/vendor/ImGuizmo"


group "Dependencies"
	include "Crimson/vendor/GLFW"
	include "Crimson/vendor/imgui"
	include "Crimson/vendor/Glad"
	include "Crimson/vendor/Chroma"
	include "Crimson/vendor/yaml_cpp"
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
		"%{IncludeDir.curl}/**.h",
		"%{IncludeDir.curl}/**.c",
		"%{IncludeDir.curl}/**.cpp",
		"%{IncludeDir.json}/**.h",
		"%{IncludeDir.json}/**.cpp",
		"%{IncludeDir.json}/**.c",
		"%{IncludeDir.entt}/**.hpp",
		"%{IncludeDir.assimp}/**.h",
		"%{IncludeDir.assimp}/**.cpp",
		"%{IncludeDir.assimp}/**.hpp",
		"%{IncludeDir.Physx}/**.h",
		"%{IncludeDir.Physx}/**.hpp",
		"%{IncludeDir.Physx}/**.cpp",
		"%{IncludeDir.oidn}/**.h",
		"%{IncludeDir.oidn}/**.hpp",
		"%{IncludeDir.ImGuizmo}/**.h",
		"%{IncludeDir.ImGuizmo}/**.cpp",
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.Stb}",
		"%{IncludeDir.curl}",
		"%{IncludeDir.json}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.Physx}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.oidn}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"opengl32.lib",

		"GLFW",
		"Glad",
		"ImGui",
		"Chroma",
		"ImGui",
		"yaml_cpp",

		"Normaliz.lib",
		"Ws2_32.lib",
		"Wldap32.lib",
		"Crypt32.lib",
		"advapi32.lib",
		"Crimson/vendor/Curl/lib/libcurl_a_debug.lib",
		"Crimson/vendor/assimp/lib/Release/assimp-vc142-mt.lib",
		"Crimson/vendor/physx_x64-windows/lib/LowLevel_static_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/LowLevelAABB_static_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/LowLevelDynamics_static_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/PhysX_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/PhysXCharacterKinematic_static_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/PhysXCommon_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/PhysXCooking_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/PhysXExtensions_static_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/PhysXFoundation_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/PhysXPvdSDK_static_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/PhysXTask_static_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/PhysXVehicle_static_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/SceneQuery_static_64.lib",
		"Crimson/vendor/physx_x64-windows/lib/SimulationController_static_64.lib",
		"Crimson/vendor/oidn/lib/OpenImageDenoise.lib",
		"Crimson/vendor/oidn/lib/OpenImageDenoise_core.lib",
	}

	filter "files:vendor/imguizmo/**.cpp"
		flags{"NoPCH"}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CN_PLATFORM_WINDOWS",
			"CN_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			--"NDEBUG",
			"PX_PHYSX_STATIC_LIB"
		}

	
	filter "toolset:msc"
		buildoptions { "/utf-8", "/arch:SSE", "/arch:AVX" }
	filter "toolset:gcc or toolset:clang"
		buildoptions { "-msse", "-mavx" }
	

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
		"%{prj.name}/Assets/**.png",
        "%{prj.name}/vendor/glm/glm"
    }



	includedirs
	{
		"Crimson/vendor/spdlog/include",
		"Crimson/src",
		"Crimson/vendor",

		"%{IncludeDir.Chroma}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.curl}",
		"%{IncludeDir.json}",
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


project "Crimson_Editor"

	location "Crimson_Editor"
		kind "ConsoleApp"
		language "c++"
		staticruntime "off"
		cppdialect "c++17"
	
		targetdir ("bin/"..outputdir.."/%{prj.name}")
		objdir ("bin-int/"..outputdir.."/%{prj.name}")
	
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/Assets/**.png"
		}
		includedirs
		{
			"Crimson/vendor/spdlog/include",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.entt}",
			"%{IncludeDir.curl}",
			"%{IncludeDir.json}",
			"Crimson/src",
			"%{IncludeDir.Physx}",
			"%{IncludeDir.yaml_cpp}"
		}
		links "Crimson"
	
		filter "system:windows"
			
			systemversion "latest"
	
			defines
			{
				"CN_PLATFORM_WINDOWS"
			}
			
		filter "configurations:Debug"
			defines "CN_DEBUG"
			runtime "Debug"
			symbols "On"
	
		filter "configurations:Release"
			defines "CN_RELEASE"
			runtime "Release"
			optimize "On"
	
		filter "configurations:Dist"
			defines "CN_DIST"
			runtime "Release"
			optimize "On"
	
			project "CameraProperties"
	
		
	location "CameraProperties"
		kind "ConsoleApp"
		language "c++"
		staticruntime "on"
		cppdialect "c++17"
	
		targetdir ("bin/"..outputdir.."/%{prj.name}")
		objdir ("bin-int/"..outputdir.."/%{prj.name}")
	
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/Assets/**.png"
		}
		includedirs
		{
			"Crimson/vendor/spdlog/include",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.entt}",
			"%{IncludeDir.curl}",
			"%{IncludeDir.json}",
			"Crimson/src"
		}
		links "Crimson"
	
		filter "system:windows"
			
			systemversion "latest"
	
			defines
			{
				"CN_PLATFORM_WINDOWS"
			}
			
		filter "configurations:Debug"
			defines "CN_DEBUG"
			runtime "Debug"
			symbols "On"
	
		filter "configurations:Release"
			defines "CN_RELEASE"
			runtime "Release"
			optimize "On"
	
		filter "configurations:Dist"
			defines "CN_DIST"
			runtime "Release"
			optimize "On"
	