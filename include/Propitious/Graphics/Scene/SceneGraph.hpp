#ifndef PROPITIOUS_GRAPHICS_SCENE_SCENEGRAPH_HPP
#define PROPITIOUS_GRAPHICS_SCENE_SCENEGRAPH_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Scene/Entity.hpp>
#include <Propitious/Graphics/Transform.hpp>
#include <Propitious/Memory/Allocator.hpp>
#include <Propitious/Containers/HashMap.hpp>

namespace Propitious
{
	using NodeId = u32;
	const NodeId EmptyNodeId = (NodeId)(-1);

	struct PROPITIOUS_EXPORT SceneGraph
	{
		struct InstanceData
		{
			NodeId length = 0;
			NodeId capacity = 0;
			void* data = nullptr;

			EntityId* entityId = nullptr;
			Transform* localTransforms = nullptr;
			Transform* worldTransforms = nullptr;
			NodeId* parents = nullptr;
			NodeId* firstChildren = nullptr;
			NodeId* previousSibling = nullptr;
			NodeId* nextSibling = nullptr;
		};

		Allocator& allocator;
		InstanceData data;

		HashMap<NodeId> map;

		SceneGraph(Allocator& allocator = defaultAllocator());
		~SceneGraph();

		void allocate(Allocator::vol length);

		NodeId create(EntityId id, const Transform& transform);
		void destroy(NodeId id);

		NodeId getTransformId(EntityId id) const;

		inline bool isValid(NodeId id) const
		{
			return id != EmptyNodeId;
		}

		inline NodeId nodeCount() const
		{
			return data.length;
		}

		inline NodeId getNodeId(EntityId id) const
		{
			return get(map, id, EmptyNodeId);
		}

		void link(NodeId parent, NodeId child);
		void unlink(NodeId child);

		inline void transformChild(NodeId id, const Transform& transform)
		{
			data.worldTransforms[id] = data.localTransforms[id] * transform;
			NodeId child = data.firstChildren[id];
			while (isValid(child))
			{
				transformChild(child, data.worldTransforms[id]);
				child = data.nextSibling[child];
			}
		}

		void updateLocal(NodeId id);
		void updateWorld(NodeId id);

		Transform getLocalTransform(NodeId id) const;
		Transform getWorldTransform(NodeId id) const;

		void setLocalTransform(NodeId id, const Transform& t);
		void setWorldTransform(NodeId id, const Transform& t);
	};
}

#endif