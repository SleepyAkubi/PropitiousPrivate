project "Utility (Engine)"
	kind "SharedLib"
	filename("utility")
	language "C++"
	characterset ("MBCS")
	targetname "utility"
	location("../../engine/utility/")
	
	includedirs 
	{ 
		"../../engine/math/include/",
		"../../engine/engine/include/",
		"../../engine/memory/include/",
		"../../engine/utility/include/",
		"../../engine/graphics/include/",
	}
	files { "../../engine/utility/src/UnityBuild.cpp" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG", "PROPITIOUS_UTILITY_EXPORTS" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG", "PROPITIOUS_UTILITY_EXPORTS" }
		optimize "On"
		
	filter "platforms:x86"
		implibdir ("../../game/build/bin32")
		targetdir ("../../game/build/bin32")
		objdir "../../engine/utility/obj32"
	filter "platforms:x64"
		implibdir ("../../game/build/bin64")
		targetdir ("../../game/build/bin64")
		objdir "../../engine/utility/obj64"