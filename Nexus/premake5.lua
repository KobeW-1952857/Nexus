project "Nexus"
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++20"
	
	targetdir ("%{wks.location}/Nexus/bin/" .. outputdir)
	objdir ("%{wks.location}/Nexus/obj/" .. outputdir)
	
	includedirs {
		"vendor/spdlog/include",
		"vendor/GLFW/include",
		"vendor/Glad/include",
		"vendor/ImGui",
		"include"
	}

	files { 
		"include/Nexus/**.h",
		"src/**.cpp"
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

	