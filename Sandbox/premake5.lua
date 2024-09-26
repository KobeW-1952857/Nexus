project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")
	
	includedirs {
		"%{wks.location}/Nexus/include",
		"%{wks.location}/Nexus/vendor/spdlog/include",
		"%{wks.location}/Nexus/vendor/glfw/include",
		"%{wks.location}/Nexus/vendor/glad/include",
		"%{wks.location}/Nexus/vendor/ImGui",
	}
	
	files { 
		"src/**.h",
		"src/**.cpp"
	}
	
	links {
		"Nexus",
		"glfw",
		"glad",
		"ImGui"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"