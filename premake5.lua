workspace "Archive"
	configurations { "Debug", "Release" }
	architecture "x86_64"

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

project "Archive.Interop"
	location "Archive.Interop"
	kind "SharedLib"
	
	language "C++"
	links { "Archive" }
	
	files { "Archive.Interop/*.cpp", "Archive.Interop/*.hpp" }
	
    filter "configurations:Debug"
        defines { "DEBUG", "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        symbols "On"

externalproject "Archive.Managed"
	location "Archive.Managed"
	uuid "9A19103F-16F7-4668-BE54-9A1E7A4F7556"
	kind "SharedLib"
	language "C#"
