#ifndef PROPITIOUS_GRAPHICS_COLOUR_HPP
#define PROPITIOUS_GRAPHICS_COLOUR_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Vector3.hpp>
#include <cmath>

namespace Propitious {

	union PROPITIOUS_EXPORT Colour
	{
		u8 data[4];
		struct
		{
			u8 r, g, b, a;
		};
	};

	inline Vector3 normalise(Colour colour)
	{
		Vector3 lightIntensities;
		lightIntensities.r = (f32)(colour.r) / (f32)(255);
		lightIntensities.g = (f32)(colour.g) / (f32)(255);
		lightIntensities.b = (f32)(colour.b) / (f32)(255);

		return lightIntensities;
	}
}

#endif
