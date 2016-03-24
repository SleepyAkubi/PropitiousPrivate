#ifndef PROPITIOUS_GRAPHICS_SCENE_ENTITY_HPP
#define PROPITIOUS_GRAPHICS_SCENE_ENTITY_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Common.hpp>
#include <Propitious/Math/Vector3.hpp>

#include <string>

namespace Propitious
{
	using EntityId = u32;

	const usize MaxEntityCount = static_cast<usize>(100);

	enum ComponentId
	{
		ComponentNone = 0x0000000000,
		ComponentName = 0x0000000001,
	};

	struct PROPITIOUS_GRAPHICS_EXPORT PositionComponent
	{
		Vector3 position;
	};

	struct PROPITIOUS_GRAPHICS_EXPORT NameComponent
	{
		std::string name;
	};
}

#endif
