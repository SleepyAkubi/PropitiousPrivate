include "memory.lua"
include "executable.lua"
include "gamelauncher.lua"
include "math.lua"
include "utility.lua"
include "graphics.lua"
include "render.lua"
include "rendergl.lua"
	
project "Engine (Engine)"
	kind "SharedLib"
	characterset ("MBCS")
	filename("engine")
	language "C++"
	location("../../engine/engine/")
	dependson "Memory (Engine)"
	dependson "Render (Engine)"
	dependson "Graphics (Engine)"
	dependson "Utility (Engine)"
	dependson "Math (Engine)"
	
	links { "opengl32", "math", "memory", "utility", "graphics", "render" }
	
	includedirs 
	{ 
		"../../engine/engine/include/",
		"../../engine/math/include/",
		"../../engine/memory/include/",
		"../../engine/utility/include/",
		"../../engine/render/include/",
		"../../engine/graphics/include/"
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
		libdirs   {"../../game/build/bin64"}
		implibdir ("../../game/build/bin32")
		targetdir ("../../game/build/bin32")
		objdir     "../../engine/engine/obj32"
	filter "platforms:x64"
		targetname "engine"
		libdirs   {"../../game/build/bin64"}
		implibdir ("../../game/build/bin64")
		targetdir ("../../game/build/bin64")
		objdir     "../../engine/engine/obj64"