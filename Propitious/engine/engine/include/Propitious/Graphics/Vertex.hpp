#ifndef PROPITIOUS_GRAPHICS_VERTEX_HPP
#define PROPITIOUS_GRAPHICS_VERTEX_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Vector2.hpp>
#include <Propitious/Math/Vector3.hpp>
#include <Propitious/Graphics/Colour.hpp>

#include <vector>

namespace Propitious
{
	struct PROPITIOUS_EXPORT Vertex
	{
		Vector3 position = { 0, 0, 0 };
		Vector2 texCoord = { 0, 0 };
		Colour colour = { 255, 255, 255 };
		Vector3 normal = { 0, 0, 0 };
		Vector3 tangent = { 0, 0, 0 };
	};

	inline Vertex vertex(Vector3 position = { 0, 0, 0 }, Vector2 texCoord = Vector2{ 0, 0 }, Vector3 normal = { 0, 0, 0 }, Vector3 tangent = { 0, 0, 0 }, Colour colour = { 255, 255, 255 })
	{
		Vertex vertex = Vertex{};
		vertex.position = position;
		vertex.texCoord = texCoord;
		vertex.colour = colour;
		vertex.normal = normal;
		vertex.tangent = tangent;

		return vertex;
	}
}

#endif
