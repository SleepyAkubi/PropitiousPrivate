#ifndef PROPITIOUS_GRAPHICS_GEOMETRYBUFFER_HPP
#define PROPITIOUS_GRAPHICS_GEOMETRYBUFFER_HPP

#include <Propitious/Common.hpp>

#include <cassert>
#include <type_traits>

namespace Propitious
{
	struct Texture;

	interface GeometryBuffer
	{
		virtual b8 create(u32 width, u32 height) = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
	};
}

#endif
