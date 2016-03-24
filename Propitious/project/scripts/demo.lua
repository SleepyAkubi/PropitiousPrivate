workspace "DemoGame"
	filename("DemoGame")
	location("../../")
	configurations { "Debug", "Release" }
	platforms { "x64", "x86" }

project "Client (DemoGame)"
	floatingpoint "Fast"
	characterset ("MBCS")
	kind "SharedLib"
	filename("client_demo")
	language "C++"
	location("../../game/src/client/")
	targetname "client"
	dependson "Game Launcher (Engine)"
	dependson "Launcher Executable (Engine)"
	dependson "Game Launcher (Engine)"
	dependson "Engine (Engine)"
	
	debugargs("-game demo")
   
	links { "opengl32", "engine", "math", "memory", "utility", "graphics", "render" }

	includedirs 
	{ 
		"../../engine/engine/include/",
		"../../engine/math/include/",
		"../../engine/memory/include/",
		"../../engine/utility/include/",
		"../../engine/graphics/include/",
		"../../engine/render/include/",
		"../../game/client/include/",
		"../../game/shared/include/",
	}
	files { "../../game/src/client/UnityBuild.cpp" }

	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	  
	filter "platforms:x86"
		libdirs { "../../game/build/bin32" }
		debugcommand ("../../game/build/game32.exe")
		targetdir ("../../game/build/demo/bin32")
	filter "platforms:x64"
		libdirs { "../../game/build/bin64" }
		debugcommand ("../../game/build/game64.exe")
		targetdir ("../../game/build/demo/bin64")
		
include "engine.lua"