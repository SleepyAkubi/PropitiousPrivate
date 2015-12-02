#ifndef PROPITIOUS_INITIALISE_HPP
#define PROPITIOUS_INITIALISE_HPP

#include <Propitious/Memory/Memory.hpp>
#include <Propitious/Graphics/OpenGL.hpp>

namespace Propitious
{
	enum Initialisers : u32
	{
		InitMemory = 1,
		InitOpenGL = 2,
	};

	void initialise(u32 initialisers)
	{
		if (initialisers & (u32)Initialisers::InitMemory)
			Implementation::initialiseMemory();
		if (initialisers & (u32)Initialisers::InitOpenGL)
		OpenGL::init();
	}
}

#endif
