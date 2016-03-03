#include <Propitious/Graphics/OpenGL.hpp>

namespace Propitious
{

	namespace OpenGL
	{
		void init()
		{
			auto result = OpenGL::System::LoadFunctions();
			AssertMsg(result, "OpenGL Failed to Load!");
		}
	}
}