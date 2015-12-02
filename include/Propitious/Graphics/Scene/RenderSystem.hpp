#ifndef PROPITIOUS_GRAPHICS_SCENE_RENDERSYSTEM_HPP
#define PROPITIOUS_GRAPHICS_SCENE_RENDERSYSTEM_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Scene/RenderComponent.hpp>
#include <Propitious/Graphics/Scene/SceneGraph.hpp>
#include <Propitious/Graphics/Scene/Entity.hpp>
#include <Propitious/Graphics/Scene/Lighting.hpp>
#include <Propitious/Graphics/RenderContext.hpp>
#include <Propitious/Graphics/GeometryBuffer.hpp>
#include <Propitious/Graphics/Camera.hpp>
#include <Propitious/Graphics/Texture.hpp>
#include <Propitious/Graphics/Scene/RenderTexture.hpp>
#include <Propitious/Containers/HashMap.hpp>
#include <Propitious/Containers/Array.hpp>
#include <Propitious/Memory/Allocator.hpp>

namespace Propitious
{
	class PROPITIOUS_EXPORT RenderSystem
	{
	public:
		using Instance = u32;
		const Instance EmptyComponent = (Instance)(-1);

		struct InstanceData
		{
			u32 length = 0;
			u32 capacity = 0;
			void* data = nullptr;

			EntityId* entityId = nullptr;
			RenderComponent* component = nullptr;
		};

		Allocator& allocator;
		InstanceData data;
		HashMap<Instance> map;
		RenderContext context;

		SceneGraph& sceneGraph;
		GeometryBuffer geometryBuffer;
		RenderTexture lightBuffer;
		RenderTexture outTexture;

		const Camera* camera;
		const ShaderProgram* currentShader;
		const Texture* currentTexture;

		BaseLight ambientLight;

		Array<DirectionalLight> directionalLights;
		Array<PointLight> pointLights;
		Array<SpotLight> spotLights;

		Dimensions frameBufferSize;

		//

		RenderSystem(Allocator& allocator, SceneGraph& scenegraph, RenderContext context);
		~RenderSystem() = default;

		void allocate(u32 length);
		Instance create(EntityId id, const RenderComponent& component);
		void destroy(Instance id);

		Instance getInstance(EntityId id);
		bool isValid(Instance instance) const;
		void render();

		void geometryPass();
		void lightPass();
		void outPass();

		void renderAmbientLight();
		void renderDirectionalLights();
		void renderPointLights();
		void renderSpotLights();

		void setShaders(const ShaderProgram* shaders);
		void setTexture(const Texture* texture, u32 position = 0);

		void clean();
	};
}

#endif