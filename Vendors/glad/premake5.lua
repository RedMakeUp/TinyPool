project "glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		"include"
	}

	files
	{
		"include/**.h",
		"src/**.c"
	}

	filter "system:windows"
        systemversion "latest"

	filter { "system:windows","configurations:Release" }
        runtime "Release"
        buildoptions "/MT"
        optimize "on"

	filter { "system:windows","configurations:Debug" }
        runtime "Debug"
        buildoptions "/MTd"
        symbols "on"
