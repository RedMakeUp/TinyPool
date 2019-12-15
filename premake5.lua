workspace "TinyPool"
    architecture "x64"
    startproject "App"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Vendors/glfw-3.3/include"
IncludeDir["glad"] = "Vendors/glad/include"
IncludeDir["spdlog"] = "Vendors/spdlog/include"
IncludeDir["glm"] = "Vendors/glm-master"
IncludeDir["assimp_core"] = "Vendors/assimp-master/include"
IncludeDir["assimp_config"] = "Vendors/assimp-master/build/include"

group "Dependencies"
    include "Vendors/glfw-3.3"
    include "Vendors/glad"
    --include "Vendors/spdlog"

group ""

project "TinyPool"
    location "TinyPool"
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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.assimp_core}",
        "%{IncludeDir.assimp_config}"
        --"%{IncludeDir.spdlog}"
    }

    links
    {
        "GLFW",
        "glad",
        --"spdlog",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "RMU_DEBUG"
        runtime "Debug"
        symbols "on"

        libdirs
        {
          "Libs/Debug"
        }

        links
        {
          "assimp-vc142-mtd.lib"
        }

    filter "configurations:Release"
        defines "RMU_RELEASE"
        runtime "Release"
        optimize "on"

        libdirs
        {
          "Libs/Release"
        }

        links
        {
          "assimp-vc142-mt.lib"
        }
