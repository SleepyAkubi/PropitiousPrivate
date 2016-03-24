project "RenderGL (Engine)"
	kind "SharedLib"
	filename("rendergl")
	language "C++"
	characterset ("MBCS")
	targetname "rendergl"
	location("../../engine/rendergl/")
	
	includedirs 
	{ 
		"../../engine/math/include/",
		"../../engine/engine/include/",
		"../../engine/memory/include/",
		"../../engine/utility/include/",
		"../../engine/graphics/include/",
		"../../engine/render/include/",
		"../../engine/rendergl/include/",
	}
	
	links { "math", "memory", "utility", "graphics", "render" }
	
	files { "../../engine/rendergl/src/UnityBuild.cpp" }
	
	filter "configurations:Debug"
		defines { "DEBUG", "_DEBUG", "PROPITIOUS_RENDERGL_EXPORTS" }
		flags { "Symbols" }

	filter "configurations:Release"
		defines { "NDEBUG", "PROPITIOUS_RENDERGL_EXPORTS" }
		optimize "On"
		
	filter "platforms:x86"
		libdirs   {"../../game/build/bin32"}
		implibdir ("../../game/build/bin32")
		targetdir ("../../game/build/bin32")
		objdir "../../engine/rendergl/obj32"
	filter "platforms:x64"
		libdirs   {"../../game/build/bin64"}
		implibdir ("../../game/build/bin64")
		targetdir ("../../game/build/bin64")
		objdir "../../engine/rendergl/obj64"