workspace "Nexus"
	configurations { "Debug", "Release" }
	architecture "x86_64"
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	files { 
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp"
	}

	includedirs {
		"%{prj.location}/src"
	}

	
	filter ""
	
project "Nexus"
	location "Nexus"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	
	targetdir ("%{prj.location}/bin/" .. outputdir)
	
	includedirs {
		"%{prj.location}/vendor/spdlog/include",
		"%{prj.location}/include"
	}
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		-- filter "system:macosx"
		-- 	links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework", "CoreVideo.framework" }
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	
	targetdir ("%{prj.location}/bin/" .. outputdir)
	
	includedirs {
		"Nexus/include",
		"Nexus/vendor/spdlog/include"
	}
	
	files { 
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp"
	}
	
	links {
		"Nexus"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"