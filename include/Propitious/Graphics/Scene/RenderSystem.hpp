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
		RenderContext* context;

		SceneGraph* sceneGraph;
		GeometryBuffer geometryBuffer;
		RenderTexture lightBuffer;
		RenderTexture outTexture;

		Camera* camera;
		const ShaderProgram* currentShader;
		const Texture* currentTexture;

		BaseLight ambientLight;

		Array<DirectionalLight> directionalLights;
		Array<PointLight> pointLights;
		Array<SpotLight> spotLights;

		Dimensions frameBufferSize;

		RenderSystem(Allocator& allocator, RenderContext* context);

		virtual void allocate(u32 length);
		virtual Instance create(EntityId id, const RenderComponent& component);
		virtual void destroy(Instance id);

		virtual Instance getInstance(EntityId id);
		virtual bool isValid(Instance instance) const;

		virtual void render() = 0;

		virtual void setShaders(const ShaderProgram* shaders);
		virtual void setTexture(const Texture* texture, u32 position = 0);

		virtual void clean();

		u32 renderMode;
	};
}

#endif