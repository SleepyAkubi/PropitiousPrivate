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
		Vector3 position = Vector3{ 0, 0, 0 };
		Vector2 texCoord = Vector2{ 0, 0 };
		Colour colour = { 255, 255, 255 };
		Vector3 normal = Vector3{ 0, 0, 0 };
	};

	inline Vertex vertex(Vector3 position = { 0, 0, 0 }, Vector2 texCoord = Vector2{ 0, 0 }, Colour colour = { 255, 255, 255 }, Vector3 normal = { 0, 0, 0 })
	{
		Vertex vertex = Vertex{};
		vertex.position = position;
		vertex.texCoord = texCoord;
		vertex.colour = colour;
		vertex.normal = normal;

		return vertex;
	}
}

#endif
