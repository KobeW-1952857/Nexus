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
		"%{prj.location}/include",
		"%{prj.location}/vendor",
		"%{prj.location}/vendor/Glad/include",
		"%{prj.location}/vendor/GLFW/include",
		"%{prj.location}/vendor/glm/glm",
		"%{prj.location}/vendor/ImGui",
		"%{prj.location}/vendor/spdlog/include",
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

	