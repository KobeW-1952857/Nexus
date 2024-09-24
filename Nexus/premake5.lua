project "Nexus"
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++20"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")
	
	includedirs {
		"vendor/spdlog/include",
		"vendor/GLFW/include",
		"vendor/glad/include",
		"include"
	}

	files { 
		"include/Nexus/**.h",
		"src/**.cpp",
		"src/Log.cpp"
	}

	links {
		"glfw",
		"glad"
	}
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"

	