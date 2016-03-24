#ifndef PROPITIOUS_GRAPHICS_MESH_HPP
#define PROPITIOUS_GRAPHICS_MESH_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Vertex.hpp>
#include <Propitious/Containers/Array.hpp>

#include <vector>

namespace Propitious
{
	enum class PROPITIOUS_EXPORT AttribLocation : u32
	{
		Position = 0,
		TexCoord = 1,
		Colour = 2,
		Normal = 3,
		Tangent = 4,
	};

	class Renderer;

	struct PROPITIOUS_GRAPHICS_EXPORT MeshData
	{
		Array<Vertex> vertices;
		Array<u32> indices;

		MeshData(Allocator& a = defaultAllocator());
		MeshData(const MeshData& other) = default;
		~MeshData() = default;

		MeshData& addFace(u32 a, u32 b, u32 c);
		MeshData& addFace(u32 offset, u32 a, u32 b, u32 c);

		void generateNormals();
	};

	inline MeshData& addFace(MeshData& mesh, u32 a, u32 b, u32 c)
	{
		return mesh.addFace(a, b, c);
	}

	inline MeshData& addFace(MeshData& mesh, u32 offset, u32 a, u32 b, u32 c)
	{
		return mesh.addFace(offset, a, b, c);
	}

	inline void generateNormals(MeshData& mesh)
	{
		return mesh.generateNormals();
	}
}

#endif
