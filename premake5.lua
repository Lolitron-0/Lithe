workspace "Lithe"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}	
IncludeDir["spdlog"] =				"%{wks.location}/Lithe/thirdparty/spdlog/include"
IncludeDir["GLFW"] =				"%{wks.location}/Lithe/thirdparty/GLFW/include"
IncludeDir["Glad"] =				"%{wks.location}/Lithe/thirdparty/glad/include"
IncludeDir["ImGui"] =				"%{wks.location}/Lithe/thirdparty/ImGui/"
IncludeDir["glm"] =					"%{wks.location}/Lithe/thirdparty/glm/"
IncludeDir["RenderAbstraction"] =	"%{wks.location}/Lithe/thirdparty/RenderAbstraction/include"
IncludeDir["EnTT"] =				"%{wks.location}/Lithe/thirdparty/EnTT/include"
IncludeDir["IconFontCppHeaders"] =	"%{wks.location}/Lithe/thirdparty/IconFontCppHeaders"
IncludeDir["ImGuizmo"] =			"%{wks.location}/Lithe/thirdparty/ImGuizmo"
IncludeDir["Profiler"] =			"%{wks.location}/Lithe/thirdparty/RenderAbstraction/thirdparty/Profiler/include"

group "Dependencies"
	include "Lithe/thirdparty/GLFW"
	include "Lithe/thirdparty/Glad"
	include "Lithe/thirdparty/ImGui"
group ""

include "Lithe/thirdparty/RenderAbstraction"

project "Lithe"
	location "Lithe"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ltpch.h"
	pchsource "Lithe/src/ltpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.inl",
		"%{prj.name}/src/**.cpp",

		"%{prj.location}/thirdparty/ImGuizmo/ImGuizmo.h",
		"%{prj.location}/thirdparty/ImGuizmo/ImGuizmo.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.RenderAbstraction}",
		"%{IncludeDir.EnTT}",
		"%{IncludeDir.IconFontCppHeaders}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.Profiler}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui", 
		"RenderAbstraction", 
		"opengl32.lib",
	}

	filter "files:Lithe/thirdparty/ImGuizmo/**.cpp"
	flags { "NoPCH" }
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"LT_PLATFORM_WINDOWS", 
			"LT_BUILD_STATIC",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS",
			"RA_WINDOWS",
		}

	filter "configurations:Debug"
		defines { "LT_DEBUG", "PROFILER_ENABLE" }
		symbols "On"
	filter "configurations:Release"
		defines "LT_RELEASE"
		optimize "On"
		symbols "Off"
	filter "configurations:Dist"
		defines "LT_DIST"
		optimize "On"
		symbols "Off"
	
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Lithe/src",
		"%{wks.location}/Lithe/thirdparty",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.RenderAbstraction}",
		"%{IncludeDir.EnTT}",
	}

	links
	{
		"Lithe"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"LT_PLATFORM_WINDOWS",
			"RA_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LT_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "LT_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "LT_DIST"
		optimize "On"

include "Lithe-Editor"
