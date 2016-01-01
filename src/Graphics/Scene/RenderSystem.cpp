#include <Propitious/Graphics/Scene/RenderSystem.hpp>
#include <Propitious/Graphics/Texture.hpp>
#include <cstdio>


namespace Propitious
{
	RenderSystem::RenderSystem(Allocator& allocator, SceneGraph& scenegraph, RenderContext context)
		: allocator(allocator)
		, data()
		, map(allocator)
		, sceneGraph(scenegraph)
		, geometryBuffer()
		, lightBuffer()
		, camera(nullptr)
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
	void RenderSystem::render()
	{
		::Propitious::create(geometryBuffer, frameBufferSize.width, frameBufferSize.height);

		geometryPass();
		lightPass();
		outPass();
	}

	void RenderSystem::geometryPass()
	{
		OpenGL::Enable(OpenGL::TEXTURE_2D);
		OpenGL::Enable(OpenGL::DEPTH_TEST);
		auto& shaders = context.shaderHolder->get("deferredGeometryPass");

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

				shaders.setUniform("u_material.diffuseMap", (u32)0);
				shaders.setUniform("u_material.diffuseColour", component.material.diffuseColour);
				shaders.setUniform("u_material.specularColour", component.material.specularColour);
				shaders.setUniform("u_material.specularExponent", component.material.specularExponent);
				shaders.setUniform("u_gamma", context.gamma);
				// TODO: Improve below line! Maybe cache NodeIds or transforms or something?
				shaders.setUniform("u_transform", sceneGraph.getWorldTransform(sceneGraph.getNodeId(entityId)));
				setTexture(component.material.diffuseMap, 0);

				draw(component.mesh);
			}
			OpenGL::Flush();
		}
		unbind<GeometryBuffer>();
	}
	void RenderSystem::lightPass()
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
			OpenGL::DepthMask(OpenGL::TRUE_);
		}

		unbind<RenderTexture>();
	}
	void RenderSystem::outPass()
	{

		::Propitious::create(outTexture, geometryBuffer.width, geometryBuffer.height, RenderTexture::Colour);
		bind(geometryBuffer.diffuse, 0);
		bind(lightBuffer.colourTexture, 1);

		bind(outTexture);
		{
			OpenGL::ClearColor(1, 1, 1, 1);
			OpenGL::Viewport(0, 0, outTexture.width, outTexture.height);
			OpenGL::Clear(OpenGL::COLOR_BUFFER_BIT);

			auto& shaders = context.shaderHolder->get("target");

			shaders.use();
			shaders.setUniform("u_diffuse", 0);
			shaders.setUniform("u_lighting", 1);

			draw(context.meshHolder->get("quad"));
		}
		unbind<RenderTexture>();
	}

	void RenderSystem::renderAmbientLight()
	{
		auto& shaders = context.shaderHolder->get("deferredAmbientLight");
		Vector3 lightIntensities = normalise(ambientLight.colour);
		lightIntensities *= ambientLight.brightness;
		shaders.use();
		shaders.setUniform("u_light.intensities", lightIntensities);
		// TODO: Cache this quad on initialisation or context update?
		draw(context.meshHolder->get("quad"));
	}
	void RenderSystem::renderDirectionalLights()
	{
		auto& shaders = context.shaderHolder->get("deferredDirectionalLight");
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
			draw(context.meshHolder->get("quad"));
		}
	}
	void RenderSystem::renderPointLights()
	{
		auto& shaders = context.shaderHolder->get("deferredPointLight");
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
			draw(context.meshHolder->get("quad"));
		}
	}
	void RenderSystem::renderSpotLights()
	{
		auto& shaders = context.shaderHolder->get("deferredSpotLight");
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
			draw(context.meshHolder->get("quad"));
		}
	}

	inline void RenderSystem::setShaders(const ShaderProgram* shaders)
	{
		if (shaders != currentShader)
		{
			currentShader = shaders;
			currentShader->use();
		}
	}
	inline void RenderSystem::setTexture(const Texture* texture, u32 position)
	{
		if (texture != currentTexture)
		{
			currentTexture = texture;
			bind(*currentTexture, position);
		}
	}

	void RenderSystem::clean()
	{
		camera = nullptr;
		currentTexture = nullptr;
		currentShader = nullptr;
	}
}