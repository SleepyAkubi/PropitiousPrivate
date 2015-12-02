#ifndef PROPITIOUS_GRAPHICS_SCENE_ENTITYWORLD_HPP
#define PROPITIOUS_GRAPHICS_SCENE_ENTITYWORLD_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Scene/Entity.hpp>
#include <Propitious/Graphics/Scene/SceneGraph.hpp>
#include <Propitious/Graphics/Scene/RenderSystem.hpp>
#include <Propitious/Graphics/Camera.hpp>
#include <Propitious/Math/Vector3.hpp>


namespace Propitious
{
	class PROPITIOUS_EXPORT EntityWorld
	{
	public:
		u32 components[MaxEntityCount];

		NameComponent names[MaxEntityCount];

		SceneGraph sceneGraph;
		Camera camera;
		RenderSystem renderSystem;

		EntityWorld();
		EntityWorld(RenderContext context);
		~EntityWorld() = default;
		EntityId createEntity();
		void setContext(RenderContext context);
		bool alive(EntityId id);
		void destroy(EntityId id);
		void render();
	};
}

#endif