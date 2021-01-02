workspace "Hovel"
    architecture "x64"
    startproject "Sandbox"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"    

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hovel/vendor/GLFW/include"
IncludeDir["Glad"] = "Hovel/vendor/Glad/include"
IncludeDir["ImGui"] = "Hovel/vendor/imgui"

include "Hovel/vendor/GLFW"
include "Hovel/vendor/Glad"
include "Hovel/vendor/imgui"

project "Hovel"
	location "Hovel"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hvpch.h"
	pchsource "Hovel/src/hvpch.cpp"

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

        systemversion "latest"

        defines 
        {
            "HV_PLATFORM_WINDOWS",
            "HV_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
        }

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "HV_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Hovel/vendor/spdlog/include",
        "Hovel/src"
    } 

    links
    {
        "Hovel"
    }
    filter "system:windows"
        cppdialect "C++17"

        systemversion "latest"

        defines 
        {
            "HV_PLATFORM_WINDOWS"
        }

	filter "configurations:Debug"
		defines "HV_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HV_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HV_DIST"
		runtime "Release"
		optimize "On"
