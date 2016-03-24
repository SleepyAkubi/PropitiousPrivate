#ifndef PROPITIOUS_GRAPHICS_SCENE_RENDERSYSTEM_HPP
#define PROPITIOUS_GRAPHICS_SCENE_RENDERSYSTEM_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Render/Common.hpp>

#include <Propitious/Containers/HashMap.hpp>
#include <Propitious/Graphics/Scene/SceneGraph.hpp>
#include <Propitious/Graphics/Camera.hpp>
#include <Propitious/Render/Texture.hpp>
#include <Propitious/Render/ShaderProgram.hpp>
#include <Propitious/Graphics/Scene/SceneGraph.hpp>
#include <Propitious/Graphics/Scene/Lighting.hpp>
#include <Propitious/Graphics/Dimensions.hpp>

namespace Propitious
{
	class Window;
	class ShaderManager;
	class MeshManager;
	class MaterialManager;
	class TextureManager;
	class RenderComponent;
	class GeometryBuffer;
	struct Camera;
	class RenderTexture;

	class PROPITIOUS_RENDER_EXPORT RenderSystem
	{
	public:
		using Instance = u32;
		const Instance EmptyComponent = (Instance)(-1);

		struct RenderContext
		{
			Window* window;
			ShaderManager* shaderHolder;
			MeshManager* meshHolder;
			MaterialManager* materialHolder;
			TextureManager* textureHolder;
			f32 gamma;
		};
		RenderContext context;

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

		SceneGraph sceneGraph;
		GeometryBuffer* geometryBuffer;
		Camera camera;

		BaseLight ambientLight;
		Array<DirectionalLight> directionalLights;
		Array<PointLight> pointLights;
		Array<SpotLight> spotLights;

		Dimensions frameBufferSize;

		RenderSystem(Allocator& allocator);
		~RenderSystem() = default;

		void allocate(u32 length);
		Instance create(EntityId id, const RenderComponent& component);
		void destroy(Instance id);

		Instance getInstance(EntityId id);
		bool isValid(Instance instance) const;

		virtual void render() = 0;

		inline void setShaders(const ShaderProgram* shaders)
		{
			if (shaders != currentShader)
			{
				currentShader = shaders;
				currentShader->use();
			}
		}
		inline void setTexture(const Texture* texture, u32 position)
		{
			if (texture != currentTexture)
			{
				currentTexture = texture;
				currentTexture->bind(position);
			}
		}

		void clean();
	private:
		const ShaderProgram* currentShader;
		const Texture* currentTexture;

		RenderTexture* lightBuffer;
		RenderTexture* outTexture;
	};
}

#endif