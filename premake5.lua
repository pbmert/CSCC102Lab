workspace "CSCC102Lab"
    architecture "x86_64"
    configurations { "Debug", "Release" }

project "Lab63"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "%{wks.location}/bin/%{prj.name}/%{cfg.buildcfg}"

    files { "activities/Lab63/src/**.cpp" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"
