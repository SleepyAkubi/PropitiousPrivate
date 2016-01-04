#include <Propitious/Graphics/Mesh.hpp>
#include <Propitious/Graphics/OpenGL.hpp>

namespace Propitious
{
	MeshData::MeshData(Allocator& a)
		: drawType(DrawType::Triangles)
		, vertices(a)
		, indices(a)
	{}

	void MeshData::generateNormals()
	{
		for (u32 i = 0; i < length(indices); i += 3)
		{
			Vertex& v0 = vertices[indices[i + 0]];
			Vertex& v1 = vertices[indices[i + 1]];
			Vertex& v2 = vertices[indices[i + 2]];

			const Vector3 pos0 = v1.position - v0.position;
			const Vector3 pos1 = v2.position - v1.position;

			const Vector2 st0 = v1.texCoord - v0.texCoord;
			const Vector2 st1 = v2.texCoord - v1.texCoord;

			const Vector3 normal = normalize(cross(pos0, pos1));

			const f32 length = 1.0f / (st0.x * st1.y - st0.y * st1.x);
			const Vector3 tangent = normalize((pos0 * st1.y - pos1 * st1.y) * length);

			v0.normal += normal;
			v0.tangent += tangent;
			v1.normal += normal;
			v1.tangent += tangent;
			v2.normal += normal;
			v2.tangent += tangent;
		}

		// TODO: change this usize

		for (usize i = 0; i < length(vertices); i++)
		{
			vertices[i].normal = normalize(vertices[i].normal);
			vertices[i].tangent = normalize(vertices[i].tangent);
		}
	}

	MeshData& MeshData::addFace(u32 a, u32 b, u32 c)
	{
		append(indices, a);
		append(indices, b);
		append(indices, c);

		return *this;
	}
	MeshData& MeshData::addFace(u32 offset, u32 a, u32 b, u32 c)
	{
		append(indices, offset + a);
		append(indices, offset + b);
		append(indices, offset + c);

		return *this;
	}

	Mesh generate(const MeshData& data)
	{
		Mesh mesh;
		mesh.drawType = data.drawType;
		mesh.drawCount = (u32)length(data.indices);

		OpenGL::GenBuffers(1, &mesh.vbo);
		OpenGL::GenBuffers(1, &mesh.ibo);

		OpenGL::BindBuffer(OpenGL::ARRAY_BUFFER, mesh.vbo);
		OpenGL::BufferData(OpenGL::ARRAY_BUFFER, sizeof(Vertex) * length(data.vertices), &data.vertices[0], OpenGL::STATIC_DRAW);

		OpenGL::BindBuffer(OpenGL::ELEMENT_ARRAY_BUFFER, mesh.ibo);
		OpenGL::BufferData(OpenGL::ELEMENT_ARRAY_BUFFER, sizeof(u32) * length(data.indices), &data.indices[0], OpenGL::STATIC_DRAW);

		return mesh;
	}

	void draw(const Mesh& mesh)
	{
		OpenGL::BindBuffer(OpenGL::ARRAY_BUFFER, mesh.vbo);
		OpenGL::BindBuffer(OpenGL::ELEMENT_ARRAY_BUFFER, mesh.ibo);

		OpenGL::VertexAttribPointer((u32)AttribLocation::Position,
			3,
			OpenGL::FLOAT,
			OpenGL::FALSE_,
			sizeof(Vertex), // Stride
			(const GLvoid*)(0));
		OpenGL::VertexAttribPointer((u32)AttribLocation::TexCoord,
			2,
			OpenGL::FLOAT,
			OpenGL::FALSE_,
			sizeof(Vertex), // Stride
			(const GLvoid*)(sizeof(Vector3)));
		OpenGL::VertexAttribPointer((u32)AttribLocation::Colour,
			4,
			OpenGL::UNSIGNED_BYTE,
			OpenGL::TRUE_,
			sizeof(Vertex), // Stride
			(const GLvoid*)(sizeof(Vector3) + sizeof(Vector2)));
		OpenGL::VertexAttribPointer((u32)AttribLocation::Normal,
			3,
			OpenGL::FLOAT,
			OpenGL::FALSE_,
			sizeof(Vertex), // Stride
			(const GLvoid*)(sizeof(Vector3) + sizeof(Vector2) + sizeof(Colour)));
		OpenGL::VertexAttribPointer((u32)AttribLocation::Tangent,
			3,
			OpenGL::FLOAT,
			OpenGL::FALSE_,
			sizeof(Vertex), // Stride
			(const GLvoid*)(sizeof(Vector3) + sizeof(Vector2) + sizeof(Colour) + sizeof(Vector3)));

		OpenGL::DrawElements((i32)mesh.drawType, mesh.drawCount, OpenGL::UNSIGNED_INT, nullptr);
	}

	void destroy(Mesh& mesh)
	{
		OpenGL::DeleteBuffers(1, &mesh.vbo);
		OpenGL::DeleteBuffers(1, &mesh.ibo);
	}
}
