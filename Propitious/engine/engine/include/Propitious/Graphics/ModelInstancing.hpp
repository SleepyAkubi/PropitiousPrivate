#ifndef PROPITIOUS_GRAPHICS_MODELINSTANCING_HPP
#define PROPITIOUS_GRAPHICS_MODELINSTANCING_HPP

#include <Propitious/Graphics/Transform.hpp>
#include <Propitious/Graphics/Material.hpp>

namespace Propitious
{
	struct Mesh;

	struct PROPITIOUS_EXPORT ModelAsset
	{
		Material* material;
		Mesh* mesh;
	};

	struct PROPITIOUS_EXPORT ModelInstance
	{
		const ModelAsset* asset;
		Transform transform;
	};
}

#endif
