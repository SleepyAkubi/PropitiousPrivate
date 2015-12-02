#ifndef PROPITIOUS_GRAPHICS_TEXTURE_HPP
#define PROPITIOUS_GRAPHICS_TEXTURE_HPP

#include <Propitious/Common.hpp>

#include <Propitious/Graphics/Image.hpp>
#include <Propitious/Graphics/OpenGL.hpp>

namespace Propitious
{
	enum class PROPITIOUS_EXPORT TextureFilter : i32
	{
		Linear,
		Nearest,
	};

	enum class PROPITIOUS_EXPORT TextureWrapMode : i32
	{
		Clamp,
		Repeat,
		ClampToEdge,
		ClampToBorder,
		MirroredRepeat,
	};

	class RenderTexture;
	struct GeometryBuffer;

	struct PROPITIOUS_EXPORT Texture
	{
	public:
		u32 width;
		u32 height;

		u32 object;
	};

	void PROPITIOUS_EXPORT bind(const Texture& texture, u32 position);

	bool PROPITIOUS_EXPORT loadFromFile(Texture& texture, const char* fileName,
		TextureFilter minMagFilter = TextureFilter::Linear,
		TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);

	bool PROPITIOUS_EXPORT loadFromImage(Texture& texture, const Image& image,
		TextureFilter minMagFilter = TextureFilter::Linear,
		TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge);
}

#endif // BGAME_TEXTURE_H
