workspace "Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

group "Engine"

project "Engine"
	location "engine"
	kind "StaticLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")
	
	pchheader "engine_pch.h"
	pchsource "engine/precompiled/engine_pch.cpp"
	
	files
	{
		"%{prj.name}/enginecode/**.h",
		"%{prj.name}/enginecode/**.cpp",
		"engine/precompiled/engine_pch.h",
		"engine/precompiled/engine_pch.cpp"
	}

	includedirs
	{
		"%{prj.name}/enginecode/",
		"%{prj.name}/enginecode/include/independent",
		"%{prj.name}/precompiled/",
		"vendor/spdlog/include",
		"vendor/glfw/include",
		"vendor/Glad/include",
		"vendor/glm/",
		"vendor/stb_image",
		"vendor/freetype2/include",
		"vendor/assimp/include",
		"vendor/Box2D",
		"vendor/ImGui",
		"vendor/FMOD/core/inc",
		"vendor/FMOD/fsbank/inc",
		"vendor/FMOD/studio/inc"
	}
	
	links 
	{
		"GLFW",
		"Glad",
		"Freetype",
		"assimp",
		"ImGui"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}
				debugenvs
		{
			"PATH=PATH;../vendor/FMOD/core/lib/x64;../vendor/FMOD/studio/lib/x64"
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "On"
		libdirs 
        {
            "../../vendor/Box2D/x64/Debug",
			"../../vendor/FMOD/core/lib/x64",
			"../../vendor/FMOD/fsbank/lib/x64",
			"../../vendor/FMOD/studio/lib/x64"
        }
		

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"
		libdirs 
        {
            "../../vendor/Box2D/x64/Release",
			"./vendor/FMOD/core/lib/x64",
			"./vendor/FMOD/fsbank/lib/x64",
			"./vendor/FMOD/studio/lib/x64"
        }
		

project "Sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/include",
		"engine/enginecode/",
		"engine/enginecode/include/independent",
		"engine/precompiled/",
		"vendor/Glad/include",
		"vendor/glm/",
		"vendor/spdlog/include",
		"vendor/Box2D",
		"vendor/ImGui",
		"vendor/FMOD/core/inc",
		"vendor/FMOD/fsbank/inc",
		"Vendor/FMOD/studio/inc"
	}

	links
	{
		"Engine",
		
		"fmodL_vc.lib",
		"fmodstudioL_vc.lib"
	}
	libdirs
	{
			
			"vendor/FMOD/core/lib/x64",
			"vendor/FMOD/fsbank/lib/x64",
			"vendor/FMOD/studio/lib/x64"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}
		debugenvs
		{
			"PATH=PATH;./vendor/FMOD/core/lib/x64;./vendor/FMOD/studio/lib/x64"
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "On"
		libdirs 
        {
            
        }
		links
		{
			"Engine",
			"fmodL_vc.lib",
			"fmodstudioL_vc.lib"
		}

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"
		libdirs 
        {
            
        }
		links
		{
			"Engine",
			"fmod_vc.lib",
			"fmodstudio_vc.lib"
		}

 project "EngineTests"
		location "engineTests"
        kind "ConsoleApp"
        language "C++"
		staticruntime "off"
		systemversion "latest"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("build/" .. outputdir .. "/%{prj.name}")

        files 
		{ 
			"%{prj.name}/include/*.h",
			"%{prj.name}/src/*.cpp"
		}

        includedirs
		{ 
			"%{prj.name}/include/",
			"vendor/googletest/googletest/include",
			"engine/enginecode/",
			"engine/enginecode/include/independent",
			"engine/enginecode/include/platform",
			"engine/precompiled/",
			"vendor/spdlog/include",
			"vendor/glfw/include",
			"vendor/Glad/include",
			"vendor/glm/",
			"vendor/stb_image",
			"vendor/freetype2/include",
			"vendor/ImGui"
			
		}

        links 
		{ 
			"googletest"
		}
		
		filter "configurations:Debug"
			runtime "Debug"
			symbols "On"
			libdirs 
        {
            "../../vendor/Box2D/x64/Debug"
        }

		filter "configurations:Release"
			runtime "Release"
			optimize "On"
		libdirs 
        {
            "../../vendor/Box2D/x64/Release"
        }

project "Spike"
	location "spike"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/include",
		"vendor/spdlog/include",
		"vendor/stb_image",
		"vendor/freetype2/include",
		"vendor/glm/",
		"vendor/assimp/include",
		"vendor/Glad/include",
		"vendor/ImGui"
	}
	
	links 
	{
		"Freetype",
		"assimp",
		"Glad",
		"ImGui"
	}
	

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

group "Vendor"



	include "vendor/glfw"
	include "vendor/googletest"
	include "vendor/Glad"
	include "vendor/freetype2"
	include "vendor/zlib"
	include "vendor/IrrXML"
	include "vendor/assimp"
	include "vendor/ImGui"
