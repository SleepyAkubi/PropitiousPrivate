#ifndef PROPITIOUS_RESOURCE_HOLDERS_TEXTUREMANAGER_HPP
#define PROPITIOUS_RESOURCE_HOLDERS_TEXTUREMANAGER_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Utility/File.hpp>
#include <Propitious/Resource/ResourceManager.hpp>
#include <Propitious/Render/Texture.hpp>

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
			Texture* tex = new Texture;
			bool loaded = tex.get()->loadFromFile(cString(String("textures/") + fileName), minMagFilter, wrapMode, filesystem);
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
			bool loaded = tex.get()->loadFromImage(image, minMagFilter, wrapMode);
			if (loaded)
				insert(id, std::move(tex));

			return loaded;
		}
	};
}

#endif