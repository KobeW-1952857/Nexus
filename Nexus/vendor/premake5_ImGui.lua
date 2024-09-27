project "ImGui"
	location "ImGui"
	kind "StaticLib"
	language "C++"
	warnings "off"
	cppdialect "C++17"

	targetdir ("%{wks.location}/Nexus/bin/" .. outputdir)
	objdir ("%{wks.location}/Nexus/obj/" .. outputdir)

	files
	{
		"%{prj.location}/*.h",
		"%{prj.location}/*.cpp",
		"%{prj.location}/misc/cpp/imgui_stdlib.cpp",
		"%{prj.location}/backends/imgui_impl_glfw.h",
		"%{prj.location}/backends/imgui_impl_glfw.cpp",
		"%{prj.location}/backends/imgui_impl_opengl3.h",
		"%{prj.location}/backends/imgui_impl_opengl3.cpp"
	}

	includedirs
	{
		"%{prj.location}",
		"%{prj.location}/backends"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"