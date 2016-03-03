project "Launcher Executable (Engine)"
	kind "WindowedApp"
	filename("executable")
	language "C++"
	location("../../engine/executable/")
	
	dependson "Engine (Engine)"
	dependson "Game Launcher (Engine)"
	
	includedirs 
		{ 
			"../../engine/executable",
			"../../engine/engine/include/" 
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

project "Game Launcher (Engine)"
	kind "SharedLib"
	filename("game_launcher")
	language "C++"
	targetname "gamelauncher"
	location("../../engine/gamelauncher/")
	
	dependson "Engine (Engine)"
	
	includedirs 
		{ 
			"../../engine/gamelauncher/include/",
			"../../engine/engine/include/" 
		}
	files { "../../engine/gamelauncher/src/UnityBuild.cpp" }
	
	links { "engine" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		
	filter "platforms:x86"
		targetdir ("../../game/build/bin32")
		libdirs { "../../game/build/bin32" }
		objdir "../../engine/gamelauncher/obj32"
	filter "platforms:x64"
		targetdir ("../../game/build/bin64")
		libdirs { "../../game/build/bin64" }
		objdir "../../engine/gamelauncher/obj64"
		
project "Engine (Engine)"
	kind "SharedLib"
	filename("engine")
	language "C++"
	location("../../engine/engine/")
	
	links { "opengl32" }
	
	includedirs 
	{ 
		"../../engine/engine/include/" 
	}
	files { "../../engine/engine/src/UnityBuild.cpp" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG", "PROPITIOUS_EXPORTS" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG", "PROPITIOUS_EXPORTS" }
		optimize "On"
		
	filter "platforms:x86"
		targetname "engine"
		implibdir ("../../game/build/bin32")
		targetdir ("../../game/build/bin32")
		objdir "../../engine/engine/obj32"
	filter "platforms:x64"
		targetname "engine"
		implibdir ("../../game/build/bin64")
		targetdir ("../../game/build/bin64")
		objdir "../../engine/engine/obj64"