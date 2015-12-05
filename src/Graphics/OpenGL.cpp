#include <Propitious/Graphics/OpenGL.hpp>

namespace Propitious
{

	namespace OpenGL
	{
		void init()
		{
			OpenGL::System::LoadFunctions();

			OpenGL::Enable(OpenGL::CULL_FACE);
			OpenGL::CullFace(OpenGL::BACK);
			OpenGL::Enable(OpenGL::DEPTH_TEST);
			OpenGL::DepthFunc(OpenGL::LESS);

			OpenGL::ClearColor(0, 0, 0, 1);

			OpenGL::EnableVertexAttribArray((u32)AttribLocation::Position);
			OpenGL::EnableVertexAttribArray((u32)AttribLocation::TexCoord);
			OpenGL::EnableVertexAttribArray((u32)AttribLocation::Colour);
			OpenGL::EnableVertexAttribArray((u32)AttribLocation::Normal);

			OpenGL::BlendFunc(OpenGL::ONE, OpenGL::ONE);
		}
	}
}