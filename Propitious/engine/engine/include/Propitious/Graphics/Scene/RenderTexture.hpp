#ifndef PROPITIOUS_GRAPHICS_SCENE_RENDERTEXTURE
#define PROPITIOUS_GRAPHICS_SCENE_RENDERTEXTURE

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/OpenGL.hpp>
#include <Propitious/Graphics/Texture.hpp>

namespace Propitious
{
	struct PROPITIOUS_EXPORT RenderTexture
	{
		enum TextureType
		{
			Colour = 1,
			Depth = 2,
			ColourDepth = Colour | Depth,
			Lighting = 4 | Colour,
		};

		Texture colourTexture;
		Texture depthTexture;
		TextureType type = Colour;

		u32 fbo = 0;
		u32 width = 0;
		u32 height = 0;
	};

	PROPITIOUS_EXPORT void bind(const RenderTexture& renderTexture);

	PROPITIOUS_EXPORT void create(RenderTexture& texture, u32 width, u32 height, RenderTexture::TextureType type);

	template<typename T>
	PROPITIOUS_EXPORT void flush();

	template<typename T>
	PROPITIOUS_EXPORT void unbind();

	template<>
	PROPITIOUS_EXPORT void flush<RenderTexture>();
	template<>
	PROPITIOUS_EXPORT void unbind<RenderTexture>();
}

#endif
