workspace "TestEnvironment"
	architecture "x64"
	startproject "Parsing" 

	configurations {
		"Debug",
		"Release",
	}

solutionDir = "%{wks.location}/"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includeDirs = {}
includeDirs["NLOHMANN"] = "vendor/NLOHMANN/single_include"

libraryDirs = {}

include "Parsing"
include "Traits"
