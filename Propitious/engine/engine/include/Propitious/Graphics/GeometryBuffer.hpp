#ifndef PROPITIOUS_GRAPHICS_GEOMETRYBUFFER_HPP
#define PROPITIOUS_GRAPHICS_GEOMETRYBUFFER_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/OpenGL.hpp>
#include <Propitious/Graphics/Texture.hpp>

#include <cassert>
#include <type_traits>

namespace Propitious
{
	struct PROPITIOUS_EXPORT GeometryBuffer
	{
		Texture diffuse;  // diffuse color (rgb)
		Texture specular; // specular color (rgb), smoothness (a)
		Texture normal;    // world normal (rgb)
						   // Texture emission;
		Texture depth;

		u32 width;
		u32 height;

		u32 fbo;
	};

	inline void bind(const GeometryBuffer& buffer)
	{
		OpenGL::BindFramebuffer(OpenGL::FRAMEBUFFER, buffer.fbo);
	}

	PROPITIOUS_EXPORT bool create(GeometryBuffer& gbuffer, u32 width, u32 height);

	template <typename T>
	PROPITIOUS_EXPORT void unbind();

	template <>
	PROPITIOUS_EXPORT void unbind<GeometryBuffer>();
}

#endif
