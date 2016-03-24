#ifndef PROPITIOUS_GRAPHICS_SCENE_SCENEGRAPH_HPP
#define PROPITIOUS_GRAPHICS_SCENE_SCENEGRAPH_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Common.hpp>

#include <Propitious/Graphics/Scene/Entity.hpp>
#include <Propitious/Graphics/Transform.hpp>
#include <Propitious/Memory/Allocator.hpp>
#include <Propitious/Containers/HashMap.hpp>

namespace Propitious
{
	using NodeId = u32;
	const NodeId EmptyNodeId = (NodeId)(-1);

	struct PROPITIOUS_GRAPHICS_EXPORT SceneGraph
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

		Transform SceneGraph::getLocalTransform(NodeId id) const
		{
			return data.localTransforms[id];
		}

		Transform SceneGraph::getWorldTransform(NodeId id) const
		{
			return data.worldTransforms[id];
		}

		////////////////

		Vector3 SceneGraph::getLocalPosition(NodeId id) const
		{
			return getLocalTransform(id).position;
		}

		Quaternion SceneGraph::getLocalOrientation(NodeId id) const
		{
			return getLocalTransform(id).orientation;
		}

		Vector3 SceneGraph::getLocalScale(NodeId id) const
		{
			return getLocalTransform(id).scale;
		}

		Vector3 SceneGraph::getWorldPosition(NodeId id) const
		{
			return getWorldTransform(id).position;
		}

		Quaternion SceneGraph::getWorldOrientation(NodeId id) const
		{
			return getWorldTransform(id).orientation;
		}

		Vector3 SceneGraph::getWorldScale(NodeId id) const
		{
			return getWorldTransform(id).scale;
		}


		void SceneGraph::setLocalTransform(NodeId id, const Transform& t)
		{
			data.localTransforms[id] = t;
			updateLocal(id);
		}

		void SceneGraph::setWorldTransform(NodeId id, const Transform& t)
		{
			data.worldTransforms[id] = t;
			updateWorld(id);
		}

		void SceneGraph::setLocalPosition(NodeId id, const Vector3& position)
		{
			data.localTransforms[id].position = position;
			updateLocal(id);
		}

		void SceneGraph::setLocalOrientation(NodeId id, const Quaternion& orientation)
		{
			data.localTransforms[id].orientation = orientation;
			updateLocal(id);
		}

		void SceneGraph::setLocalScale(NodeId id, const Vector3& scale)
		{
			data.localTransforms[id].scale = scale;
			updateLocal(id);
		}

		void SceneGraph::setWorldPosition(NodeId id, const Vector3& position)
		{
			data.worldTransforms[id].position = position;
			updateWorld(id);
		}

		void SceneGraph::setWorldOrientation(NodeId id, const Quaternion& orientation)
		{
			data.worldTransforms[id].orientation = orientation;
			updateWorld(id);
		}

		void SceneGraph::setWorldScale(NodeId id, const Vector3& scale)
		{
			data.worldTransforms[id].scale = scale;
			updateWorld(id);
		}

	};
}

#endif