project "Lithe-Editor"
	kind "ConsoleApp"

	language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.hpp",
		"%{prj.location}/src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Lithe/src",
		"%{wks.location}/Lithe/thirdparty",
		"%{prj.location}/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.RenderAbstraction}",
		"%{IncludeDir.EnTT}",
        "%{IncludeDir.IconFontCppHeaders}",
        "%{IncludeDir.ImGuizmo}",
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
