project "spdlog"
  kind "StaticLib"
  language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/spdlog/**.h",
        "src/**.cpp"
  }

  includedirs
	{
		"include"
	}

	filter "system:windows"
        systemversion "latest"
        staticruntime "On"

		defines
		{
            "SPDLOG_COMPILED_LIB"
		}

    filter { "system:windows","configurations:Release" }
        runtime "Release"
        buildoptions "/MT"
        optimize "on"

    filter { "system:windows","configurations:Debug" }
        runtime "Debug"
        buildoptions "/MTd"
        symbols "on"
