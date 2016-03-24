#ifndef PROPITIOUS_GRAPHICS_MATERIAL_HPP
#define PROPITIOUS_GRAPHICS_MATERIAL_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Colour.hpp>

namespace Propitious {

	class Texture;

	struct PROPITIOUS_EXPORT Material
	{
		// TODO: remove pointers
		Texture* diffuseMap = nullptr;
		Colour diffuseColour = Colour{ 255, 255, 255, 255 };

		Texture* normalMap = nullptr;

		Colour specularColour = diffuseColour;
		f32 specularExponent = 80.0f;
	};
}

#endif
