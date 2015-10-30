#include <Propitious/Graphics/Image.hpp>

#define STBI_FAILURE_USERMSG

#define STB_IMAGE_IMPLEMENTATION
#pragma warning (push, 0)
#include "STB/stb_image.h"
#pragma warning (pop)

#include <stdexcept>

#include <iostream>
#include <Propitious/Memory/Allocator.hpp>

namespace Propitious
{
	bool loadFromFile(Image& image, const char* fileName)
	{
		int width, height, format;
		u8* loadedImageByteArray = stbi_load(fileName, &width, &height, &format, 0);

		if (!loadedImageByteArray)
		{
			std::cout << stbi_failure_reason() << std::endl;
			// (TODO): Error Logging
			return false;
		}

		loadFromMemory(image, width, height, (ImageFormat)format, loadedImageByteArray);
		stbi_image_free(loadedImageByteArray);

		if (image.pixels)
			return true;
		return false;
	}

	bool loadFromMemory(Image& image, u32 w, u32 h, ImageFormat f, const u8* p)
	{

		image.width = w;
		image.height = h;
		image.format = f;

		usize imageSize = w * h * static_cast<int>(f);

		Allocator& allocator = defaultAllocator();

		if (image.pixels)
			allocator.deallocate(image.pixels);

		image.pixels = (u8*)(allocator.allocate(imageSize * sizeof(u8)));

		if (p != nullptr)
			std::memcpy(image.pixels, p, imageSize);

		return true;
	}


	u8* getPixel(const Image& image, u32 column, u64 row)
	{
		if (column >= image.width || row >= image.height)
			return nullptr;

		return image.pixels + (row * image.width + column) * static_cast<usize>(image.format);
	}

	void setPixel(Image& image, u32 column, u64 row, const u32* pixel)
	{
		if (column >= image.width || row >= image.height)
			return;

		u8* p = getPixel(image, column, row);
		std::memcpy(p, pixel, static_cast<int>(image.format));
	}


	void flipVertically(Image& image)
	{
		usize pitch = image.width * static_cast<usize>(image.format);
		u32 halfRows = image.height / 2;

		Allocator& allocator = defaultAllocator();
		u8* rowBuffer = (u8*)allocator.allocate(pitch * sizeof(u8));

		for (u32 i = 0; i < halfRows; i++)
		{
			u8* row = image.pixels + (i * image.width) * static_cast<usize>(image.format);
			u8* oppositeRow = image.pixels + ((image.height - i - 1) * image.width) * static_cast<usize>(image.format);

			std::memcpy(rowBuffer, row, pitch);
			std::memcpy(row, oppositeRow, pitch);
			std::memcpy(oppositeRow, rowBuffer, pitch);
		}

		allocator.deallocate(rowBuffer);
	}

	/*
	void Image::rotate90CCW()
	{
	// (TODO): Implement function
	}


	void Image::copyRectFromImage(const Image& src,
	u32 srcCol,  u32 srcRow,
	u32 destCol, u32 destRow,
	u32 m_width,   u32 m_height)
	{
	// (TODO): Implement function
	}
	*/

}
