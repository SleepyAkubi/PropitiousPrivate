#include <Propitious/Graphics/Image.hpp>

#include <stdexcept>

#include <iostream>
#include <Propitious/Memory/Allocator.hpp>

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

			dataPos = *(usize*)&(header[0x0A]);
			imageSize = *(usize*)&(header[0x22]);
			image.width = *(usize*)&(header[0x12]);
			image.height = *(usize*)&(header[0x16]);
			image.format = ImageFormat::RGB;

			if (imageSize == 0)
			{
				imageSize = image.width * image.height * 3;
			}

			if (dataPos == 0)
			{
				dataPos = 54;
			}

			image.pixels = (u8*)(defaultAllocator().allocate(imageSize));
			fread(image.pixels, 1, imageSize, file);
			fclose(file);

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
}
