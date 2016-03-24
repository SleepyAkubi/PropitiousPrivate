project "Math (Engine)"
	kind "SharedLib"
	filename("math")
	language "C++"
	characterset ("MBCS")
	targetname "math"
	location("../../engine/math/")
	
	includedirs 
	{ 
		"../../engine/math/include/",
		"../../engine/memory/include/",
		"../../engine/engine/include/",
		"../../engine/utility/include/",
		"../../engine/graphics/include/",
	}
	files { "../../engine/math/src/UnityBuild.cpp" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG", "PROPITIOUS_MATH_EXPORTS" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG", "PROPITIOUS_MATH_EXPORTS" }
		optimize "On"
		
	filter "platforms:x86"
		implibdir ("../../game/build/bin32")
		targetdir ("../../game/build/bin32")
		objdir "../../engine/math/obj32"
	filter "platforms:x64"
		implibdir ("../../game/build/bin64")
		targetdir ("../../game/build/bin64")
		objdir "../../engine/math/obj64"