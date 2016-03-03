#include <Propitious/Graphics/Scene/DeferredRenderSystem.hpp>
#include <Propitious/Graphics/Texture.hpp>
#include <cstdio>

// TODO(Preston): CACHE SHADERS!!!

namespace Propitious
{
	DeferredRenderSystem::DeferredRenderSystem(Allocator& allocator, RenderContext* context)
		: BaseClass(allocator, context)
		, shaderCache { }
	{
		
	}

	void DeferredRenderSystem::render()
	{
		if (renderMode == RenderMode::None)
			return;
		::Propitious::create(geometryBuffer, frameBufferSize.width, frameBufferSize.height);

		geometryPass();
		lightPass();
		outPass();
	}

	void DeferredRenderSystem::geometryPass()
	{
		OpenGL::Enable(OpenGL::TEXTURE_2D);
		OpenGL::Enable(OpenGL::DEPTH_TEST);
		auto& shaders = context->shaderHolder->get("deferredGeometryPass");

		bind(geometryBuffer);
		{
			OpenGL::Viewport(0, 0, geometryBuffer.width, geometryBuffer.height);
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
		unbind<GeometryBuffer>();
	}
	void DeferredRenderSystem::lightPass()
	{
		::Propitious::create(lightBuffer, geometryBuffer.width, geometryBuffer.height, RenderTexture::Lighting);

		bind(geometryBuffer.diffuse, 0);
		bind(geometryBuffer.specular, 1);
		bind(geometryBuffer.normal, 2);
		bind(geometryBuffer.depth, 3);

		bind(lightBuffer);
		{
			OpenGL::ClearColor(0, 0, 0, 0);
			OpenGL::Viewport(0, 0, lightBuffer.width, lightBuffer.height);
			OpenGL::Clear(OpenGL::COLOR_BUFFER_BIT);

			OpenGL::DepthMask(OpenGL::FALSE_);
			OpenGL::Enable(OpenGL::BLEND);
			OpenGL::Enable(OpenGL::TEXTURE_2D);
			OpenGL::BlendFunc(OpenGL::ONE, OpenGL::ONE);

			renderAmbientLight();
			renderDirectionalLights();
			renderPointLights();
			renderSpotLights();
			OpenGL::Disable(OpenGL::BLEND);
		}

		unbind<RenderTexture>();
	}
	void DeferredRenderSystem::outPass()
	{

		::Propitious::create(outTexture, geometryBuffer.width, geometryBuffer.height, RenderTexture::Colour);

		if (renderMode == RenderMode::Final)
		{
			bind(geometryBuffer.diffuse, 0);
			bind(lightBuffer.colourTexture, 1);

			bind(outTexture);
			{
				OpenGL::Viewport(0, 0, outTexture.width, outTexture.height);
				OpenGL::Clear(OpenGL::COLOR_BUFFER_BIT);

				auto& shaders = context->shaderHolder->get("deferredOutput");

				shaders.use();
				shaders.setUniform("u_diffuse", 0);
				shaders.setUniform("u_lighting", 1);
				shaders.setUniform("u_gamma", context->gamma);

				draw(context->meshHolder->get("quad"));
				OpenGL::DepthMask(OpenGL::TRUE_);
			}
			unbind<RenderTexture>();
		}
		else
		{
			if (renderMode == RenderMode::Lighting)
				bind(lightBuffer.colourTexture, 0);
			else if (renderMode == RenderMode::Normal)
				bind(geometryBuffer.normal, 0);
			else if (renderMode == RenderMode::Diffuse)
				bind(geometryBuffer.diffuse, 0);
			else if (renderMode == RenderMode::Specular)
				bind(geometryBuffer.specular, 0);
			else if (renderMode == RenderMode::Depth)
				bind(geometryBuffer.depth, 0);
			
			bind(outTexture);
			{
				OpenGL::Viewport(0, 0, outTexture.width, outTexture.height);
				OpenGL::Clear(OpenGL::COLOR_BUFFER_BIT);

				auto& shaders = context->shaderHolder->get("target");

				shaders.use();
				shaders.setUniform("u_tex", 0);

				draw(context->meshHolder->get("quad"));
				OpenGL::DepthMask(OpenGL::TRUE_);
			}
			unbind<RenderTexture>();
		}
	}

	void DeferredRenderSystem::renderAmbientLight()
	{
		auto& shaders = context->shaderHolder->get("deferredAmbientLight");
		Vector3 lightIntensities = normalise(ambientLight.colour);
		lightIntensities *= ambientLight.brightness;
		shaders.use();
		shaders.setUniform("u_light.intensities", lightIntensities);
		// TODO: Cache this quad on initialisation or context update?
		draw(context->meshHolder->get("quad"));
	}
	void DeferredRenderSystem::renderDirectionalLights()
	{
		auto& shaders = context->shaderHolder->get("deferredDirectionalLight");
		shaders.use();
		shaders.setUniform("u_specular", 1);
		shaders.setUniform("u_normal", 2);
		for (u32 i = 0; i < directionalLights.length; i++)
		{
			auto& light = directionalLights[i];
			Vector3 lightIntensities = normalise(light.colour);
			lightIntensities *= light.brightness;
			shaders.setUniform("u_light.base.intensities", lightIntensities);
			shaders.setUniform("u_light.direction", normalize(light.direction));
			draw(context->meshHolder->get("quad"));
		}
	}
	void DeferredRenderSystem::renderPointLights()
	{
		auto& shaders = context->shaderHolder->get("deferredPointLight");
		shaders.use();
		shaders.setUniform("u_specular", 1);
		shaders.setUniform("u_normal", 2);
		shaders.setUniform("u_depth", 3);
		shaders.setUniform("u_cameraInverse", Propitious::inverse(matrix(*camera)));
		//std::cout << pointLights.size() << std::endl
		for (u32 i = 0; i < pointLights.length; i++)
		{
			auto& light = pointLights[i];
			light.calculateRange();
			Vector3 lightIntensities = normalise(light.colour);
			lightIntensities *= light.brightness;
			//std::cout << light << std::endl;
			shaders.setUniform("u_light.position", light.position);
			shaders.setUniform("u_light.base.intensities", lightIntensities);
			shaders.setUniform("u_light.attenuation.constant", light.attenuation.constant);
			shaders.setUniform("u_light.attenuation.linear", light.attenuation.linear);
			shaders.setUniform("u_light.attenuation.quadratic", light.attenuation.quadratic);
			shaders.setUniform("u_light.range", light.range);
			draw(context->meshHolder->get("quad"));
		}
	}
	void DeferredRenderSystem::renderSpotLights()
	{
		auto& shaders = context->shaderHolder->get("deferredSpotLight");
		shaders.use();
		shaders.setUniform("u_specular", 1);
		shaders.setUniform("u_normal", 2);
		shaders.setUniform("u_depth", 3);
		shaders.setUniform("u_cameraInverse", Propitious::inverse(matrix(*camera)));
		//std::cout << pointLights.size() << std::endl
		for (u32 i = 0; i < spotLights.length; i++)
		{
			auto& light = spotLights[i];
			light.calculateRange();
			Vector3 lightIntensities = normalise(light.colour);
			lightIntensities *= light.brightness;
			//std::cout << light << std::endl;
			shaders.setUniform("u_light.pointLight.attenuation.constant", light.attenuation.constant);
			shaders.setUniform("u_light.pointLight.attenuation.linear", light.attenuation.linear);
			shaders.setUniform("u_light.pointLight.attenuation.quadratic", light.attenuation.quadratic);
			shaders.setUniform("u_light.pointLight.base.intensities", lightIntensities);
			shaders.setUniform("u_light.pointLight.position", light.position);
			shaders.setUniform("u_light.pointLight.range", light.range);
			shaders.setUniform("u_light.direction", light.direction);
			shaders.setUniform("u_light.coneAngle", (f32)light.coneAngle);
			draw(context->meshHolder->get("quad"));
		}
	}
}