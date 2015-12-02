#include <Propitious/Graphics/Texture.hpp>

namespace Propitious
{
	// FINISH RENDERER IMPLEMENTATION FOR TEXTURES
	static i32 getInternalFormat(ImageFormat format, bool srgb)
	{
		switch (format)
		{
		case ImageFormat::Grayscale:
			return GL_LUMINANCE;
		case ImageFormat::GrayscaleAlpha:
			return GL_LUMINANCE_ALPHA;
		case ImageFormat::RGB:
			return (srgb ? GL_SRGB : GL_RGB);
		case ImageFormat::RGBA:
			return (srgb ? GL_SRGB_ALPHA : GL_RGBA);
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
			glGenTextures(1, &texture.object);

		texture.width = (usize)image.width;
		texture.height = (usize)image.height;

		glGenTextures(1, &texture.object);
		glBindTexture(GL_TEXTURE_2D, texture.object);

		i32 minMagFilterGL;
		i32 wrapModeGL;

		switch (minMagFilter)
		{
		case TextureFilter::Linear:
			minMagFilterGL = GL_LINEAR; break;
		case TextureFilter::Nearest:
			minMagFilterGL = GL_NEAREST; break;
		}

		switch (wrapMode)
		{
		case TextureWrapMode::Clamp:
			wrapModeGL = GL_CLAMP; break;
		case TextureWrapMode::Repeat:
			wrapModeGL = GL_REPEAT; break;
		case TextureWrapMode::ClampToEdge:
			wrapModeGL = GL_CLAMP_TO_EDGE; break;
		case TextureWrapMode::ClampToBorder:
			wrapModeGL = GL_CLAMP_TO_BORDER; break;
		case TextureWrapMode::MirroredRepeat:
			wrapModeGL = GL_MIRRORED_REPEAT; break;

		}

		glTexParameteri(
			GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeGL);
		glTexParameteri(
			GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeGL);
		glTexParameteri(
			GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFilterGL);
		glTexParameteri(
			GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFilterGL);

		glTexImage2D(GL_TEXTURE_2D,
			0,
			getInternalFormat(image.format, true),
			(i32)texture.width,
			(i32)texture.height,
			0,
			getInternalFormat(image.format, false),
			GL_UNSIGNED_BYTE,
			image.pixels);


		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}


	void bind(const Texture& texture, u32 position)
	{
		if (position > 31)
			position = 31;

		glActiveTexture(GL_TEXTURE0 + position);
		//glClientActiveTexture(GL_TEXTURE0 + position);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture.object);
		glDisable(GL_TEXTURE_2D);
	}
}
