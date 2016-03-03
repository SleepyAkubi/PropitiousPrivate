workspace "DemoGame"
	filename("DemoGame")
	location("../../")
	configurations { "Debug", "Release" }
	platforms { "x64", "x86" }

project "Client (DemoGame)"
	floatingpoint "Fast"
	kind "SharedLib"
	filename("client_demo")
	language "C++"
	location("../../game/src/client/")
	targetname "client"
	dependson "Game Launcher (Engine)"
	dependson "Server (DemoGame)"
	dependson "Launcher Executable (Engine)"
	dependson "Game Launcher (Engine)"
	dependson "Engine (Engine)"
	
	debugargs("-game demo")
   
	links { "opengl32", "engine" }

	includedirs 
	{ 
		"../../engine/engine/include/",
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
	  
project "Server (DemoGame)"
	floatingpoint "Fast"
	kind "SharedLib"
	filename("server_demo")
	language "C++"
	location("../../game/src/server/")
	targetname "server"
	dependson "Engine (Engine)"
	
	links { "engine" }

	includedirs 
	{ 
		"../../engine/engine/include/",
		"../../game/server/include/",
		"../../game/shared/include/",
	}
	files { "../../game/src/server/UnityBuild.cpp" }

	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
   
	filter "platforms:x86"
		libdirs { "../../game/build/bin32" }
		targetdir "../../game/build/demo/bin32"
		objdir "../../game/src/server/obj32"
	filter "platforms:x64"
		libdirs { "../../game/build/bin64" }
		targetdir "../../game/build/demo/bin64"
		objdir "../../game/src/server/obj64"
		
include "engine.lua"