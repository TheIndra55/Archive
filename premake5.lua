workspace "Archive"
	configurations { "Debug", "Release" }

project "Archive"
	location "Archive"
	kind "StaticLib"
	
	language "C++"
	
	files { "Archive/*.cpp", "Archive/*.hpp" }
	
    filter "configurations:Debug"
        defines { "DEBUG", "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        symbols "On"

project "ArchiveTool"
	location "ArchiveTool"
	kind "ConsoleApp"
	
	language "C++"
	links { "Archive" }
	cppdialect "C++17"
	
	files { "ArchiveTool/*.cpp", "ArchiveTool/*.hpp" }

    filter "configurations:Debug"
        defines { "DEBUG", "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        symbols "On"
