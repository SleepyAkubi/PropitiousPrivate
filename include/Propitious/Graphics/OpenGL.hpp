#ifndef PROPITIOUS_GRAPHICS_OPENGL_HPP
#define PROPITIOUS_GRAPHICS_OPENGL_HPP

#include <Propitious/Graphics/Colour.hpp>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || \
	defined(__WINDOWS__)

#include <GL/gl.h>

#elif defined(__APPLE__) && defined(__MACH__)

#include <OpenGL/GL.h>

#elif defined(__unix__)

#include <GL/gl.h>

#else

#include <GL/gl.h>

#endif

namespace Propitious 
{

	namespace OpenGL
	{
		PROPITIOUS_EXPORT void init();
	}
}


#endif