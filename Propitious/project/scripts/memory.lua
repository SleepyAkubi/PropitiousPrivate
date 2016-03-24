project "Memory (Engine)"
	kind "SharedLib"
	filename("memory")
	language "C++"
	characterset ("MBCS")
	targetname "memory"
	location("../../engine/memory/")
	
	includedirs 
	{ 
		"../../engine/math/include/",
		"../../engine/engine/include/",
		"../../engine/utility/include/",
		"../../engine/memory/include/",
		"../../engine/graphics/include/",
	}
	files { "../../engine/memory/src/UnityBuild.cpp" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG", "PROPITIOUS_MEMORY_EXPORTS" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG", "PROPITIOUS_MEMORY_EXPORTS" }
		optimize "On"
		
	filter "platforms:x86"
		implibdir ("../../game/build/bin32")
		targetdir ("../../game/build/bin32")
		objdir "../../engine/memory/obj32"
	filter "platforms:x64"
		implibdir ("../../game/build/bin64")
		targetdir ("../../game/build/bin64")
		objdir "../../engine/memory/obj64"