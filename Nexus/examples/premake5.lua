project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	location "Sandbox"
	
	includedirs {
		"%{wks.location}/Nexus/include",
		"%{wks.location}/Nexus/vendor/spdlog/include",
		"%{wks.location}/Nexus/vendor/glfw/include",
		"%{wks.location}/Nexus/vendor/Glad/include",
		"%{wks.location}/Nexus/vendor/ImGui",
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