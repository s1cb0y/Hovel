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
IncludeDir["glm"] = "Hovel/vendor/glm"
IncludeDir["stb_image"] = "Hovel/vendor/stb_image"

group "Dependencies"
    include "Hovel/vendor/GLFW"
    include "Hovel/vendor/Glad"
    include "Hovel/vendor/imgui"

group ""

project "Hovel"
	location "Hovel"
	kind "StaticLib"
	language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hvpch.h"
	pchsource "Hovel/src/hvpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
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
        
        systemversion "latest"

        defines 
        {
            "HV_PLATFORM_WINDOWS",
            "HV_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
        }

	filter "configurations:Debug"
		defines "HV_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HV_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HV_DIST"
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
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Hovel/vendor/spdlog/include",
        "Hovel/src",
		"Hovel/vendor",
		"%{IncludeDir.glm}"
    } 

    links
    {
        "Hovel"
    }
    filter "system:windows"
        
        systemversion "latest"

        defines 
        {
            "HV_PLATFORM_WINDOWS"
        }

	filter "configurations:Debug"
		defines "HV_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HV_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HV_DIST"
		runtime "Release"
		optimize "on"
