#ifndef PROPITIOUS_GRAPHICS_TEXTURE_HPP
#define PROPITIOUS_GRAPHICS_TEXTURE_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Render/Common.hpp>
#include <Propitious/User/FileSystem.hpp>

#include <Propitious/Graphics/Image.hpp>

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

	abstract class PROPITIOUS_RENDER_EXPORT Texture
	{
	public:
		u32 width;
		u32 height;

		virtual void bind(u32 position) const = 0;

		b8 loadFromFile(
			const a8* fileName, 
			TextureFilter minMagFilter = TextureFilter::Linear, 
			TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge, 
			FileSystem& fileSystem = defaultFileSystem());

		virtual b8 loadFromImage(
			const Image& image,
			TextureFilter minMagFilter = TextureFilter::Linear,
			TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge) = 0;
	};
}

#endif // BGAME_TEXTURE_H
