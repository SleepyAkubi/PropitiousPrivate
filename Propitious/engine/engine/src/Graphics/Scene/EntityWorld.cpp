#include <Propitious/Graphics/Scene/EntityWorld.hpp>
#include <Propitious/Memory/Allocator.hpp>

namespace Propitious
{
	EntityWorld::EntityWorld()
		: sceneGraph(defaultAllocator())
		, components()
	{}

	EntityId EntityWorld::createEntity()
	{
		EntityId id;
		for (id = 0; id < MaxEntityCount; id++)
		{
			if (components[id] == ComponentNone)
				return id;
		}

		return MaxEntityCount;
	}

	bool EntityWorld::alive(EntityId id)
	{
		return components[id] != ComponentNone;
	}

	void EntityWorld::destroy(EntityId id)
	{
		components[id] = ComponentNone;
	}
	void EntityWorld::render(RenderSystem* renderSystem)
	{
		if (!renderSystem)
			return;
		renderSystem->clean();
		renderSystem->frameBufferSize = { 1280, 720 };
		renderSystem->camera->viewportAspectRatio = (f32)renderSystem->frameBufferSize.width / (f32)renderSystem->frameBufferSize.height;
		renderSystem->render();

		OpenGL::Viewport(0, 0, renderSystem->frameBufferSize.width, renderSystem->frameBufferSize.height);
		OpenGL::ClearColor(0, 0, 0, 1);
		OpenGL::Clear(OpenGL::COLOR_BUFFER_BIT | OpenGL::DEPTH_BUFFER_BIT);

		auto& shaders = renderSystem->context->shaderHolder->get("target");
		shaders.use();

		shaders.setUniform("u_tex", 0);

		bind(renderSystem->outTexture.colourTexture, 0);
		draw(renderSystem->context->meshHolder->get("quad"));
	}
}