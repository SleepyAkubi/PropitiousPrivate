#ifndef PROPITIOUS_GRAPHICS_DIMENSIONS_HPP
#define PROPITIOUS_GRAPHICS_DIMENSIONS_HPP

#include <Propitious/Common.hpp>

namespace Propitious
{
	struct PROPITIOUS_EXPORT Dimensions
	{
		u32 width;
		u32 height;

		Dimensions() = default;
		Dimensions(int width, int height)
			: width(width)
			, height(height)
		{}

		inline f32 getAspectRatio() const
		{
			if (width == height)
				return 1.0f;

			if (width == 0 || height == 0)
				return 1.0f;

			return static_cast<f32>(width) / static_cast<f32>(height);
		}
	};

}

#endif