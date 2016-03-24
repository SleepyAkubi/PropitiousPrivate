project "Render (Engine)"
	kind "SharedLib"
	filename("render")
	language "C++"
	characterset ("MBCS")
	targetname "render"
	location("../../engine/render/")
	
	dependson "Memory (Engine)"
	dependson "Graphics (Engine)"
	dependson "Utility (Engine)"
	dependson "Math (Engine)"
	
	includedirs 
	{ 
		"../../engine/math/include/",
		"../../engine/engine/include/",
		"../../engine/memory/include/",
		"../../engine/utility/include/",
		"../../engine/graphics/include/",
		"../../engine/render/include/",
	}
	files { "../../engine/render/src/UnityBuild.cpp" }
	
	links { "math", "memory", "utility", "graphics" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG", "PROPITIOUS_RENDER_EXPORTS" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG", "PROPITIOUS_RENDER_EXPORTS" }
		optimize "On"
		
	filter "platforms:x86"
		libdirs   {"../../game/build/bin32"}
		implibdir ("../../game/build/bin32")
		targetdir ("../../game/build/bin32")
		objdir "../../engine/render/obj32"
	filter "platforms:x64"
		libdirs   {"../../game/build/bin64"}
		implibdir ("../../game/build/bin64")
		targetdir ("../../game/build/bin64")
		objdir "../../engine/render/obj64"