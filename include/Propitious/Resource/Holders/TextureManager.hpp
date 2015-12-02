#ifndef PROPITIOUS_RESOURCE_HOLDERS_TEXTUREMANAGER_HPP
#define PROPITIOUS_RESOURCE_HOLDERS_TEXTUREMANAGER_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Utility/File.hpp>
#include <Propitious/Resource/ResourceManager.hpp>
#include <Propitious/Graphics/Texture.hpp>

namespace Propitious
{
	class TextureManager : public ResourceManager<Texture, std::string>
	{
	public:
		inline bool insertFromFile(
			const std::string& id,
			const char* fileName,
			TextureFilter minMagFilter = TextureFilter::Linear,
			TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge)
		{
			auto tex = make_unique<Texture>();
			bool loaded = loadFromFile(*tex.get(), std::string(getPathToExe() + "/textures/" + fileName).c_str(), minMagFilter, wrapMode);
			if (loaded)
				return insert(id, std::move(tex));
			return false;
		}

		inline bool insertFromImage(
			const std::string& id,
			const Image& image,
			TextureFilter minMagFilter = TextureFilter::Linear,
			TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge)
		{
			if (has(id))
				return false;

			auto tex = make_unique<Texture>();
			bool loaded = loadFromImage(*tex.get(), image, minMagFilter, wrapMode);
			if (loaded)
				insert(id, std::move(tex));

			return loaded;
		}
	};
}

#endif