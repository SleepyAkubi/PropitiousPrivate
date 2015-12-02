#ifndef PROPITIOUS_GRAPHICS_SCENE_DRAWABLE_HPP
#define PROPITIOUS_GRAPHICS_SCENE_DRAWABLE_HPP

#include <Propitious/Common.hpp>

namespace Propitious
{
	struct Transform;
	class Renderer;

	class PROPITIOUS_EXPORT Drawable
	{
	protected:
		virtual void draw(Renderer& renderer, Transform transform) const = 0;
	private:
		friend class Renderer;
	};
}

#endif
