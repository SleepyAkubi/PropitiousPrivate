#include <Propitious/Render/Texture.hpp>
#include <Propitious/Graphics/Image.hpp>

namespace Propitious
{
	bool Texture::loadFromFile(
		const char* fileName,
		TextureFilter minMagFilter,
		TextureWrapMode wrapMode,
		FileSystem& filesystem)
	{
		Image image;
		if (!::Propitious::loadFromFile(image, fileName, filesystem))
			return false;
		flipVertically(image);

		return loadFromImage(image, minMagFilter, wrapMode);
	}
}