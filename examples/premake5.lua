project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	location "Sandbox"

	targetdir ("%{prj.location}/bin/" .. outputdir)
	objdir ("%{prj.location}/obj/" .. outputdir)
	
	includedirs {
		"%{wks.location}/include",
		"%{wks.location}/vendor",
		"%{wks.location}/vendor/Glad/include",
		"%{wks.location}/vendor/glfw/include",
		"%{wks.location}/vendor/ImGui",
		"%{wks.location}/vendor/spdlog/include",
	}
	
	files { 
		"%{prj.location}/main.cpp"
	}
	
	links {
		"Nexus",
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