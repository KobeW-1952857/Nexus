workspace "Nexus"
	configurations { "Debug", "Release" }
	architecture "x86_64"
	outputdir = "%{cfg.buildcfg}-%{cfg.system}"

	filter "system:macosx"
		links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework", "QuartzCore.framework" }
		
	filter""

	include "Nexus/vendor/glfw"
	include "Nexus/vendor/glad"
	include "Nexus"
	include "Sandbox"
