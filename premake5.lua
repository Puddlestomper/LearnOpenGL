workspace "LearnOpenGL"
	architecture "x64"
	startproject "PuddleLOGL"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["GLAD"] = "vendor/GLAD/include"
-- IncludeDir["ImGui"] = "vendor/imgui"
-- IncludeDir["glm"] = "vendor/glm"
-- IncludeDir["stb_image"] = "vendor/stb_image"

group "Dependencies"
	include "vendor/GLFW"
	include "vendor/GLAD"
--	include "vendor/imgui"

group ""

project "PuddleLOGL"
	location "PuddleLOGL"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pudpch.h"
	pchsource "PuddleLOGL/src/pudpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
--		"%{prj.name}/vendor/stb_image/**.h",
--		"%{prj.name}/vendor/stb_image/**.cpp",
--		"%{prj.name}/vendor/glm/glm/**.hpp",
--		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
--		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
--		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
--		"%{IncludeDir.ImGui}",
--		"%{IncludeDir.glm}",
--		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"GLAD",
--		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"