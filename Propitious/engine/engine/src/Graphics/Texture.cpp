#include <Propitious/Graphics/Texture.hpp>

namespace Propitious
{
	// FINISH RENDERER IMPLEMENTATION FOR TEXTURES
	static i32 getInternalFormat(ImageFormat format, bool srgb)
	{
		switch (format)
		{
		case ImageFormat::Grayscale:
			return OpenGL::LUMINANCE;
		case ImageFormat::GrayscaleAlpha:
			return OpenGL::LUMINANCE_ALPHA;
		case ImageFormat::RGB:
			return (srgb ? OpenGL::SRGB : OpenGL::RGB);
		case ImageFormat::RGBA:
			return (srgb ? OpenGL::SRGB_ALPHA : OpenGL::RGBA);
		default:
			return 0;
		}
	}

	bool loadFromFile(Texture& texture, const char* fileName,
		TextureFilter minMagFilter,
		TextureWrapMode wrapMode)
	{
		Image image;
		if (!loadFromFile(image, fileName))
			return false;
		flipVertically(image);

		return loadFromImage(texture, image, minMagFilter, wrapMode);
	}

	bool loadFromImage(Texture& texture, const Image& image,
		TextureFilter minMagFilter,
		TextureWrapMode wrapMode)
	{
		if (!texture.object)
			OpenGL::GenTextures(1, &texture.object);

		texture.width = (usize)image.width;
		texture.height = (usize)image.height;

		OpenGL::GenTextures(1, &texture.object);
		OpenGL::BindTexture(OpenGL::TEXTURE_2D, texture.object);

		i32 minMagFilterGL;
		i32 wrapModeGL;

		switch (minMagFilter)
		{
		case TextureFilter::Linear:
			minMagFilterGL = OpenGL::LINEAR; break;
		case TextureFilter::Nearest:
			minMagFilterGL = OpenGL::NEAREST; break;
		}

		switch (wrapMode)
		{
		case TextureWrapMode::Clamp:
			wrapModeGL = OpenGL::CLAMP; break;
		case TextureWrapMode::Repeat:
			wrapModeGL = OpenGL::REPEAT; break;
		case TextureWrapMode::ClampToEdge:
			wrapModeGL = OpenGL::CLAMP_TO_EDGE; break;
		case TextureWrapMode::ClampToBorder:
			wrapModeGL = OpenGL::CLAMP_TO_BORDER; break;
		case TextureWrapMode::MirroredRepeat:
			wrapModeGL = OpenGL::MIRRORED_REPEAT; break;

		}

		OpenGL::TexParameteri(
			OpenGL::TEXTURE_2D, OpenGL::TEXTURE_WRAP_S, wrapModeGL);
		OpenGL::TexParameteri(
			OpenGL::TEXTURE_2D, OpenGL::TEXTURE_WRAP_T, wrapModeGL);
		OpenGL::TexParameteri(
			OpenGL::TEXTURE_2D, OpenGL::TEXTURE_MIN_FILTER, minMagFilterGL);
		OpenGL::TexParameteri(
			OpenGL::TEXTURE_2D, OpenGL::TEXTURE_MAG_FILTER, minMagFilterGL);

		OpenGL::TexImage2D(OpenGL::TEXTURE_2D,
			0,
			getInternalFormat(image.format, true),
			(i32)texture.width,
			(i32)texture.height,
			0,
			getInternalFormat(image.format, false),
			OpenGL::UNSIGNED_BYTE,
			image.pixels);


		OpenGL::BindTexture(OpenGL::TEXTURE_2D, 0);

		return true;
	}


	void bind(const Texture& texture, u32 position)
	{
		if (position > 31)
			position = 31;

		OpenGL::ActiveTexture(OpenGL::TEXTURE0 + position);

		OpenGL::Enable(OpenGL::TEXTURE_2D);
		OpenGL::BindTexture(OpenGL::TEXTURE_2D, texture.object);
		OpenGL::Disable(OpenGL::TEXTURE_2D);
	}
}
