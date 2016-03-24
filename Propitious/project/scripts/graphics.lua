project "Graphics (Engine)"
	kind "SharedLib"
	filename("graphics")
	language "C++"
	characterset ("MBCS")
	targetname "graphics"
	location("../../engine/graphics/")
	
	dependson "Utility (Engine)"
	
	includedirs 
	{ 
		"../../engine/math/include/",
		"../../engine/engine/include/",
		"../../engine/memory/include/",
		"../../engine/utility/include/",
		"../../engine/graphics/include/",
		"../../engine/render/include/",
	}
	
	links { "math", "memory", "utility" }
	
	files { "../../engine/graphics/src/UnityBuild.cpp" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG", "PROPITIOUS_GRAPHICS_EXPORTS" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG", "PROPITIOUS_GRAPHICS_EXPORTS" }
		optimize "On"
		
	filter "platforms:x86"
		libdirs   {"../../game/build/bin32"}
		implibdir ("../../game/build/bin32")
		targetdir ("../../game/build/bin32")
		objdir "../../engine/graphics/obj32"
	filter "platforms:x64"
		libdirs   {"../../game/build/bin64"}
		implibdir ("../../game/build/bin64")
		targetdir ("../../game/build/bin64")
		objdir "../../engine/graphics/obj64"