#ifndef PROPITIOUS_RENDER_MESH_HPP
#define PROPITIOUS_RENDER_MESH_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Render/Common.hpp>
#include <Propitious/Graphics/MeshData.hpp>

namespace Propitious
{
	abstract class PROPITIOUS_RENDER_EXPORT Mesh
	{
	public:
		virtual void generate(MeshData& meshData) = 0;
		virtual void draw() = 0;
	};
}

#endif
