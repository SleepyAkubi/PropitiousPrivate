#ifndef PROPITIOUS_GRAPHICS_IMAGE_HPP
#define PROPITIOUS_GRAPHICS_IMAGE_HPP

#include <Propitious/Common.hpp>

#include <string>

namespace Propitious
{

	enum class PROPITIOUS_EXPORT ImageFormat
	{
		None,
		Grayscale,
		GrayscaleAlpha,
		RGB,
		RGBA,

		NumFormats
	};

	struct PROPITIOUS_EXPORT Image
	{
		ImageFormat format = ImageFormat::None;
		u32 width = 0;
		u32 height = 0;

		u8* pixels = nullptr;
	};

	bool loadFromFile(Image& image, const char* fileName);
	bool loadFromMemory(Image& image, u32 width, u32 height, ImageFormat format, const u8* pixels = nullptr);

	u8* getPixel(const Image& image, u32 column, u64 row);
	void setPixel(Image& image, u32 column, u64 row, const u32* pixel);

	void flipVertically(Image& image);
}

#endif
