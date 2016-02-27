#ifndef PROPITIOUS_GRAPHICS_SCENE_DEFERREDRENDERSYSTEM_HPP
#define PROPITIOUS_GRAPHICS_SCENE_DEFERREDRENDERSYSTEM_HPP

#include <Propitious/Graphics/Scene/RenderSystem.hpp>

namespace Propitious
{
	class PROPITIOUS_EXPORT DeferredRenderSystem : public RenderSystem
	{
	public:
		struct ShaderCache
		{
			ShaderProgram geometryPass;
			ShaderProgram output;
			ShaderProgram target;
			ShaderProgram ambientLight;
			ShaderProgram directionalLight;
			ShaderProgram pointLight;
			ShaderProgram spotLight;
		};
		enum RenderMode : u8
		{
			Final = 0,
			Lighting = 1,
			Normal = 2,
			Diffuse = 3,
			Specular = 4,
			Depth = 5,
			None = 6,
			MaxRenderModes
		};

		DEFINE_CLASS(DeferredRenderSystem, RenderSystem);

		DeferredRenderSystem(Allocator& allocator, RenderContext* context);
		~DeferredRenderSystem() = default;

		void render();
		void cache();

		void geometryPass();
		void lightPass();
		void outPass();

		void renderAmbientLight();
		void renderDirectionalLights();
		void renderPointLights();
		void renderSpotLights();

		ShaderCache shaderCache;
	};
}

#endif