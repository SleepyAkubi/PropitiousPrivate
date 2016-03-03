#include <Propitious/Graphics/Scene/SceneGraph.hpp>
#include <Propitious/Graphics/Transform.hpp>

#include <cstdio>

namespace Propitious
{
	SceneGraph::SceneGraph(Allocator& allocator)
		: allocator(allocator)
		, data()
		, map(allocator)
	{
		allocate(16);
	}
	SceneGraph::~SceneGraph()
	{
		allocator.deallocate(data.data);
	}
	void SceneGraph::allocate(Allocator::vol length)
	{
		if (length <= data.length)
			return;

		const NodeId bytes = (NodeId)(length * (sizeof(EntityId) + 2 * sizeof(Transform) + 4 * sizeof(NodeId)));

		InstanceData newData;
		newData.length = data.length;
		newData.capacity = (NodeId)length;
		newData.data = allocator.allocate(bytes);

		newData.entityId		= (EntityId*)	(newData.data);
		newData.localTransforms = (Transform*)	(newData.entityId + length);
		newData.worldTransforms = (Transform*)	(newData.localTransforms + length);
		newData.parents			= (NodeId*)		(newData.worldTransforms + length);
		newData.firstChildren	= (NodeId*)		(newData.parents + length);
		newData.previousSibling = (NodeId*)		(newData.firstChildren + length);
		newData.nextSibling		= (NodeId*)		(newData.previousSibling + length);

		std::memcpy(newData.entityId,		 data.entityId,			 data.length * sizeof(EntityId));
		std::memcpy(newData.localTransforms, data.localTransforms,	 data.length * sizeof(Transform));
		std::memcpy(newData.worldTransforms, data.worldTransforms,	 data.length * sizeof(Transform));
		std::memcpy(newData.parents,		 data.parents,			 data.length * sizeof(NodeId));
		std::memcpy(newData.firstChildren,	 data.firstChildren,	 data.length * sizeof(NodeId));
		std::memcpy(newData.previousSibling, data.previousSibling,	 data.length * sizeof(NodeId));
		std::memcpy(newData.nextSibling,	 data.nextSibling,		 data.length * sizeof(NodeId));

		allocator.deallocate(data.data);
		data = newData;
	}
	NodeId SceneGraph::create(EntityId id, const Transform& transform)
	{
		if (data.capacity == data.length || data.capacity == 0)
			allocate(2 * data.length + 1);

		const NodeId last = data.length;
		data.entityId[last]			= id;
		data.localTransforms[last]	= transform;
		data.worldTransforms[last]	= transform;
		data.parents[last]			= EmptyNodeId;
		data.firstChildren[last]	= EmptyNodeId;
		data.previousSibling[last]	= EmptyNodeId;
		data.nextSibling[last]		= EmptyNodeId;

		set(map, id, last);

		data.length++;

		return last;

	}
	void SceneGraph::destroy(NodeId id)
	{
		const NodeId last = data.length - 1;
		const EntityId e = data.entityId[id];
		const EntityId lastEntity = data.entityId[last];

		data.entityId[id] = data.entityId[last];
		data.localTransforms[id] = data.localTransforms[last];
		data.worldTransforms[id] = data.worldTransforms[last];
		data.parents[id] = data.parents[last];
		data.firstChildren[id] = data.firstChildren[last];
		data.previousSibling[id] = data.previousSibling[last];
		data.nextSibling[id] = data.nextSibling[last];

		set(map, lastEntity, id);
		set(map, e, EmptyNodeId);

		data.length--;
	}

	NodeId SceneGraph::getTransformId(EntityId id) const
	{
		return get(map, id, EmptyNodeId);
	}

	void SceneGraph::link(NodeId parent, NodeId child)
	{
		unlink(child);

		if (!isValid(data.firstChildren[parent]))
		{
			data.firstChildren[parent] = child;
			data.parents[child] = parent;
		}
		else
		{
			NodeId previous;
			NodeId current = data.firstChildren[parent];
			while (isValid(current))
			{
				previous = current;
				current = data.nextSibling[current];
			}

			data.nextSibling[previous] = child;

			data.firstChildren[child] = EmptyNodeId;
			data.nextSibling[child] = EmptyNodeId;
			data.previousSibling[child] = previous;
		}

		const Transform parentTransform = data.worldTransforms[parent];
		const Transform childTransform = data.worldTransforms[child];

		const Transform localTransform = parentTransform / childTransform;

		data.localTransforms[child] = localTransform;
		data.parents[child] = parent;

		transformChild(child, parentTransform);
	}
	void SceneGraph::unlink(NodeId child)
	{
		if (!isValid(data.parents[child]))
			return;

		if (!isValid(data.previousSibling[child]))
			data.firstChildren[data.parents[child]] = data.nextSibling[child];
		else
			data.nextSibling[data.previousSibling[child]] = data.nextSibling[child];

		if (isValid(data.nextSibling[child]))
			data.previousSibling[data.nextSibling[child]] = data.previousSibling[child];

		data.parents[child] = EmptyNodeId;
		data.nextSibling[child] = EmptyNodeId;
		data.previousSibling[child] = EmptyNodeId;
	}

	void SceneGraph::updateLocal(NodeId id)
	{
		NodeId parentId = data.parents[id];
		Transform parentTransform = {};
		if (isValid(parentId))
			parentTransform = data.worldTransforms[parentId];
		transformChild(id, parentTransform);
	}

	void SceneGraph::updateWorld(NodeId id)
	{
		NodeId parentId = data.parents[id];
		Transform parentTransform = {};
		if (isValid(parentId))
			parentTransform = data.worldTransforms[parentId];
		data.localTransforms[id] = data.worldTransforms[id] / parentTransform;
		transformChild(id, parentTransform);
	}
}