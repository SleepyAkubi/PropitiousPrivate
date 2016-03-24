project "Launcher Executable (Engine)"
	kind "WindowedApp"
	filename("executable")
	characterset ("MBCS")
	language "C++"
	location("../../engine/executable/")
	
	dependson "Engine (Engine)"
	dependson "Game Launcher (Engine)"
	
	includedirs 
		{ 
			"../../engine/executable",
			"../../engine/engine/include/",
			"../../engine/utility/include/",
			"../../engine/math/include/",
			"../../engine/memory/include/",
			"../../engine/graphics/include/",
		}
	files { "../../engine/executable/src/UnityBuild.cpp" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		
	filter "platforms:x86"
		targetname "game32"
		targetdir ("../../game/build")
		objdir "../../engine/launcher/obj32"
	filter "platforms:x64"
		targetname "game64"
		targetdir ("../../game/build")
		objdir "../../engine/launcher/obj64"