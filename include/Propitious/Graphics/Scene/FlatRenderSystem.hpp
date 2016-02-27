#ifndef PROPITIOUS_GRAPHICS_SCENE_FLATRENDERSYSTEM_HPP
#define PROPITIOUS_GRAPHICS_SCENE_FLATRENDERSYSTEM_HPP

#include <Propitious/Graphics/Scene/RenderSystem.hpp>

namespace Propitious
{
	class PROPITIOUS_EXPORT FlatRenderSystem : public RenderSystem
	{
	public:
		DEFINE_CLASS(FlatRenderSystem, RenderSystem);

		FlatRenderSystem(Allocator& allocator, RenderContext* context);
		~FlatRenderSystem() = default;

		void render();
	};
}

#endif