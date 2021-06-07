workspace "cplox"
    configurations {"Debug", "Release"}

project "cplox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs "./include/"

    files { "**.hpp", "**.cpp", "**/**/*.hpp", "**/**/*.cpp" }
    removefiles { "./Tool/*.py" }

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"