#include <Propitious/Graphics/OpenGL.hpp>

namespace Propitious
{

	namespace OpenGL
	{
		void init()
		{
			glewInit();

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);

			glClearColor(0, 0, 0, 1);

			glEnableVertexAttribArray((u32)AttribLocation::Position);
			glEnableVertexAttribArray((u32)AttribLocation::TexCoord);
			glEnableVertexAttribArray((u32)AttribLocation::Colour);
			glEnableVertexAttribArray((u32)AttribLocation::Normal);

			glBlendFunc(GL_ONE, GL_ONE);
		}
	}
}