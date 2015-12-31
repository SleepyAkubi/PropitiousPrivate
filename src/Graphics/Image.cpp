#include <Propitious/Graphics/Image.hpp>

#include <stdexcept>

#include <iostream>
#include <Propitious/Memory/Allocator.hpp>

#include <algorithm>
#include <iterator>

namespace Propitious
{
	namespace Types
	{
		bool loadBMP(Image& image, const a8* path)
		{

			u8* header = (u8*)(defaultAllocator().allocate(54));
			u32 dataPos;
			u32 imageSize;

			FILE* file = fopen(path, "rb");
			if (!file)
			{
				return false;
			}

			if (fread(header, 1, 54, file) != 54)
			{
				return false;
			}

			if (header[0] != 'B' || header[1] != 'M')
			{
				return false;
			}

			dataPos = *(u32*)&(header[0x0A]);
			imageSize = *(u32*)&(header[0x22]);
			image.width = *(u32*)&(header[0x12]);
			image.height = *(u32*)&(header[0x16]);
			image.format = ImageFormat::RGB;

			if (imageSize == 0)
			{
				imageSize = image.width * image.height * 3;
			}

			if (dataPos == 0)
			{
				dataPos = 54;
			}

			u8* temporary = (u8*)(defaultAllocator().allocate(imageSize));

			fread(temporary, 1, imageSize, file);
			fclose(file);

			// B -> R
			u8 tempRGB = 0;
			for (usize i = 0; i < imageSize; i += 3)
			{
				tempRGB = temporary[i];
				temporary[i] = temporary[i + 2];
				temporary[i + 2] = tempRGB;
			}

			image.pixels = temporary;
			flipVertically(image);

			return true;
		}
	}

	bool loadFromFile(Image& image, const a8* path)
	{
		return Types::loadBMP(image, path);
	}

	bool loadFromMemory(Image& image, u32 w, u32 h, ImageFormat f, const u8* p)
	{

		image.width = w;
		image.height = h;
		image.format = f;

		usize imageSize = w * h * (usize)f;

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

		return image.pixels + (row * image.width + column) *  (usize)image.format;
	}

	void setPixel(Image& image, u32 column, u64 row, const u32* pixel)
	{
		if (column >= image.width || row >= image.height)
			return;

		u8* p = getPixel(image, column, row);
		std::memcpy(p, pixel, (usize)image.format);
	}


	void flipVertically(Image& image)
	{
		usize pitch = image.width *  (usize)image.format;
		u32 halfRows = image.height / 2;

		Allocator& allocator = defaultAllocator();
		u8* rowBuffer = (u8*)allocator.allocate(pitch * sizeof(u8));

		for (u32 i = 0; i < halfRows; i++)
		{
			u8* row = image.pixels + (i * image.width) *  (usize)image.format;
			u8* oppositeRow = image.pixels + ((image.height - i - 1) * image.width) *  (usize)image.format;

			std::memcpy(rowBuffer, row, pitch);
			std::memcpy(row, oppositeRow, pitch);
			std::memcpy(oppositeRow, rowBuffer, pitch);
		}

		allocator.deallocate(rowBuffer);
	}
}
