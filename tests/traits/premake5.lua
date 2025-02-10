project "traits"
	kind "ConsoleApp"
	language "C++"

	targetdir (solutionDir .. "/bin/" .. outputdir .. "/%{prj.name}")
	objdir (solutionDir .. "/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp" 

	files {
		"include/**.h",
		"src/**.cpp",
		"src/**.hpp",
		"temp/**"
	}

	includedirs {
		"include",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "on"

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"