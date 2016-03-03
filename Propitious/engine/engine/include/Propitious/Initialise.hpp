#ifndef PROPITIOUS_INITIALISE_HPP
#define PROPITIOUS_INITIALISE_HPP

#include <Propitious/Memory/Memory.hpp>
#include <Propitious/Graphics/OpenGL.hpp>

namespace Propitious
{
	void initialise()
	{
		Implementation::initialiseMemory();
	}
}

#endif
