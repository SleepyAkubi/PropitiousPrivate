#ifndef PROPITIOUS_GRAPHICS_IMAGE_HPP
#define PROPITIOUS_GRAPHICS_IMAGE_HPP

#include <Propitious/Common.hpp>
#include <Propitious/User/FileSystem.hpp>
#include <Propitious/Graphics/Common.hpp>

#include <string>

namespace Propitious
{
	enum class ImageFormat : u8
	{
		None,
		Grayscale,
		GrayscaleAlpha,
		RGB,
		RGBA,

		NumFormats
	};

	//#pragma message( PROPITIOUS_WARNING("TODO") "Fix the image class when compiling on Clang!")

	struct PROPITIOUS_GRAPHICS_EXPORT Image
	{
		ImageFormat format = ImageFormat::None;
		u32 width = 0;
		u32 height = 0;

		u8* pixels = nullptr;
	};

	PROPITIOUS_GRAPHICS_EXPORT bool loadFromFile(Image& image, const a8* fileName, FileSystem& filesys = defaultFileSystem());
	PROPITIOUS_GRAPHICS_EXPORT bool loadFromMemory(Image& image, u32 width, u32 height, ImageFormat format, const u8* pixels = nullptr);

	PROPITIOUS_GRAPHICS_EXPORT u8* getPixel(const Image& image, u32 column, u64 row);
	PROPITIOUS_GRAPHICS_EXPORT void setPixel(Image& image, u32 column, u64 row, const u32* pixel);

	PROPITIOUS_GRAPHICS_EXPORT void flipVertically(Image& image);
	
}

#endif
