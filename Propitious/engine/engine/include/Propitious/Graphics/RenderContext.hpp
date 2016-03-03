#ifndef PROPITIOUS_GRAPHICS_CONTEXT_HPP
#define PROPITIOUS_GRAPHICS_CONTEXT_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Resource/ResourceManager.hpp>
#include <Propitious/Resource/Holders.hpp>
#include <Propitious/Graphics/Window.hpp>

namespace Propitious
{
	struct RenderContext
	{
		Window* window;
		ShaderManager* shaderHolder;
		MeshManager* meshHolder;
		MaterialManager* materialHolder;
		TextureManager* textureHolder;
		f32 gamma;
	};
}

#endif