project "Liquid"
	kind "StaticLib"
	language "C++"

	targetdir (solutionDir .. "/bin/" .. outputdir .. "/%{prj.name}")
	objdir (solutionDir .. "/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"include/**.h",
		"include/**.hpp",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "on"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"