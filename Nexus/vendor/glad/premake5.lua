project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"
	warnings "off"

	targetdir ("%{wks.location}/Nexus/bin/" .. outputdir)
	objdir ("%{wks.location}/Nexus/obj/" .. outputdir)

	files
	{
		"include/glad/gl.h",
		"include/KHR/khrplatform.h",
		"src/gl.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"