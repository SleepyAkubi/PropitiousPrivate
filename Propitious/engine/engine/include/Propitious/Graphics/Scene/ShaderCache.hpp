#ifndef PROPITIOUS_GRAPHICS_SCENE_SHADERCACHE
#define PROPITIOUS_GRAPHICS_SCENE_SHADERCACHE

namespace Propitious
{
#define MAX_CACHED_SHADERS
	struct ShaderCache
	{
		ShaderProgram* shaders[64];
	};
}

#endif
