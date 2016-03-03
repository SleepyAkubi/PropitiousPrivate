#ifndef PROPITIOUS_RESOURCE_HOLDERS_MATERIALMANAGER_HPP
#define PROPITIOUS_RESOURCE_HOLDERS_MATERIALMANAGER_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Resource/ResourceManager.hpp>
#include <Propitious/Graphics/Material.hpp>

namespace Propitious
{
	class MaterialManager : public ResourceManager<Material, std::string>
	{
	public:
		inline bool addFromComponents(
			const std::string& id,
			Texture* diffuseMap,
			Texture* normalMap,
			Colour diffuseColour = { 255, 255, 255, 255 },
			f32 specularExponent = 10,
			Colour specularColour = { 255, 255, 255, 255 })
		{
			auto mat = make_unique<Material>();
			mat->diffuseMap = diffuseMap;
			mat->normalMap = normalMap;
			mat->diffuseColour = diffuseColour;
			mat->specularExponent = specularExponent;
			mat->specularColour = specularColour;

			return insert(id, std::move(mat));
		}
	};

}
#endif