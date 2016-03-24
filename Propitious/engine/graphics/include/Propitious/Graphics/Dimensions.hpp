#ifndef PROPITIOUS_GRAPHICS_DIMENSIONS_HPP
#define PROPITIOUS_GRAPHICS_DIMENSIONS_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Common.hpp>

namespace Propitious
{
	struct Dimensions
	{
		u32 width;
		u32 height;
	};

	inline f32 getAspectRatio(Dimensions dimensions)
	{
		if (dimensions.width == dimensions.height)
			return 1.0f;

		if (dimensions.width == 0 || dimensions.height == 0)
			return 1.0f;

		return (f32)dimensions.width / (f32)dimensions.height;
	}

}

#endif