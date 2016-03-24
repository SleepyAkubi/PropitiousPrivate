#include <Propitious/Render/ShaderProgram.hpp>
#include <Propitious/Render/RenderSystem.hpp>
#include <Propitious/Graphics/Scene/RenderComponent.hpp>
#include <Propitious/Render/Texture.hpp>
#include <cstdio>


namespace Propitious
{
	RenderSystem::RenderSystem(Allocator& allocator)
		: allocator(allocator)
		, data()
		, map(allocator)
		, geometryBuffer()
		, lightBuffer()
		, camera()
		, currentShader(nullptr)
		, currentTexture(nullptr)
		, context(context)
	{
	}

	void RenderSystem::allocate(u32 length)
	{
		if (length <= data.length)
			return;

		const usize bytes = length * (sizeof(EntityId) + sizeof(RenderComponent));

		InstanceData newData;
		newData.length = data.length;
		newData.capacity = length;
		newData.data = allocator.allocate(bytes);

		newData.entityId = (EntityId*)(newData.data);
		newData.component = (RenderComponent*)(newData.entityId + length);

		std::memcpy(newData.entityId, data.entityId, data.length * sizeof(EntityId));
		std::memcpy(newData.component, data.component, data.length * sizeof(RenderComponent));

		allocator.deallocate(data.data);
		data = newData;
	}
	RenderSystem::Instance RenderSystem::create(EntityId id, const RenderComponent& component)
	{
		if (data.capacity == data.length || data.capacity == 0)
			allocate(2 * data.length + 1);

		const Instance firstFree = data.length;

		data.entityId[firstFree] = id;
		data.component[firstFree] = component;

		set(map, id, firstFree);

		data.length++;

		return firstFree;
	}
	void RenderSystem::destroy(Instance id)
	{
		const Instance last = data.length - 1;
		const EntityId entity = data.entityId[id];
		const EntityId lastEntity = data.entityId[last];

		data.entityId[id] = data.entityId[last];
		data.component[id] = data.component[last];

		set(map, lastEntity, id);
		set(map, entity, EmptyComponent);

		data.length--;
	}

	inline RenderSystem::Instance RenderSystem::getInstance(EntityId id)
	{
		return get(map, id, EmptyComponent);
	}
	bool RenderSystem::isValid(Instance instance) const
	{
		return instance != EmptyComponent;
	}

	void RenderSystem::clean()
	{
		//camera = nullptr;
		currentTexture = nullptr;
		currentShader = nullptr;
	}
}