project "Game Launcher (Engine)"
	kind "SharedLib"
	filename("game_launcher")
	characterset ("MBCS")
	language "C++"
	targetname "gamelauncher"
	location("../../engine/gamelauncher/")
	
	dependson "Engine (Engine)"
	
	includedirs 
		{ 
			"../../engine/gamelauncher/include/",
			"../../engine/engine/include/" ,
			"../../engine/math/include/",
			"../../engine/utility/include/",
			"../../engine/memory/include/",
			"../../engine/graphics/include/",
			"../../engine/render/include/",
		}
	files { "../../engine/gamelauncher/src/UnityBuild.cpp" }
	
	links { "engine", "math", "memory", "utility", "graphics", "render" }
	
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