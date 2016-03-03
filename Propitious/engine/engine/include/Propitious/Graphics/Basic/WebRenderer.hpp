#ifndef PROPITIOUS_GRAPHICS_BASIC_WEBRENDERER_HPP
#define PROPITIOUS_GRAPHICS_BASIC_WEBRENDERER_HPP

#include <Propitious/Common.hpp>

namespace Propitious
{
	class PROPITIOUS_EXPORT WebRenderer
	{
	public:
		WebRenderer();
		~WebRenderer();
		void setURL();
		void render();
	};
}
#endif