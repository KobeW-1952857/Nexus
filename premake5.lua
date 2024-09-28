workspace "Nexus"
	configurations { "Debug", "Release" }
	architecture "x86_64"

	outputdir = "%{cfg.system}/%{cfg.buildcfg}"
	targetdir ("%{wks.location}/bin/" .. outputdir)
	objdir ("%{wks.location}/obj/" .. outputdir)

	startproject "Sandbox"

	filter "system:macosx"
		links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework", "QuartzCore.framework" }
		
	filter""

	include "vendor/premake5_glfw.lua"
	include "vendor/premake5_ImGui.lua"
	include "vendor/Glad"
	include "examples"

project "Nexus"
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++20"
	
	
	includedirs {
		"include",
		"vendor",
		"vendor/ImGui",
		"vendor/Glad/include",
		"vendor/GLFW/include",
		"vendor/spdlog/include",
		"vendor/glm/glm",
	}

	files { 
		"include/Nexus/**.h",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
	}

	links {
		"glfw",
		"Glad",
		"ImGui"
	}
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	