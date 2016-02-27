#include <Propitious/Graphics/Scene/FlatRenderSystem.hpp>

namespace Propitious
{
	FlatRenderSystem::FlatRenderSystem(Allocator& allocator, RenderContext* context)
		: BaseClass(allocator, context)
	{
		OpenGL::Enable(OpenGL::TEXTURE_2D);
		OpenGL::Enable(OpenGL::DEPTH_TEST);
	}


	void FlatRenderSystem::render()
	{
		OpenGL::Enable(OpenGL::TEXTURE_2D);
		OpenGL::Enable(OpenGL::DEPTH_TEST);
		auto& shaders = context->shaderHolder->get("flat");

		OpenGL::Viewport(0, 0, frameBufferSize.width, frameBufferSize.height);
		OpenGL::Clear(OpenGL::COLOR_BUFFER_BIT | OpenGL::DEPTH_BUFFER_BIT);

		shaders.use();
		shaders.setUniform("u_camera", matrix(*camera));
		shaders.setUniform("u_cameraPosition", position(*camera));

		for (u32 i = 0; i < data.length; i++)
		{
			EntityId& entityId = data.entityId[i];
			RenderComponent& component = data.component[i];


			shaders.setUniform("u_material.diffuseMap", 0);
			shaders.setUniform("u_material.normalMap", 1);
			shaders.setUniform("u_material.diffuseColour", component.material.diffuseColour);
			shaders.setUniform("u_material.specularColour", component.material.specularColour);
			shaders.setUniform("u_material.specularExponent", component.material.specularExponent);
			// TODO: Improve below line! Maybe cache NodeIds or transforms or something...
			shaders.setUniform("u_transform", sceneGraph->getWorldTransform(sceneGraph->getNodeId(entityId)));

			setTexture(component.material.diffuseMap, 0);
			setTexture(component.material.normalMap, 1);

			draw(component.mesh);
		}
		OpenGL::Flush();
	}
}