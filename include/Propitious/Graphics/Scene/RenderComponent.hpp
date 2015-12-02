#ifndef PROPITIOUS_GRAPHICS_SCENE_RENDERCOMPONENT_HPP
#define PROPITIOUS_GRAPHICS_SCENE_RENDERCOMPONENT_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Mesh.hpp>
#include <Propitious/Graphics/Material.hpp>

namespace Propitious
{
	struct PROPITIOUS_EXPORT RenderComponent
	{
		Mesh mesh;
		Material material;
	};
}

#endif
