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

			Vector3 normal = normalize(cross((v1.position - v0.position), (v2.position - v1.position)));

			v0.normal += normal;
			v1.normal += normal;
			v2.normal += normal;
		}

		// TODO: change this usize

		for (usize i = 0; i < length(vertices); i++)
			vertices[i].normal = normalize(vertices[i].normal);
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

		OpenGL::DrawElements((i32)mesh.drawType, mesh.drawCount, OpenGL::UNSIGNED_INT, nullptr);

		//OpenGL::DisableVertexAttribArray((u32)AttribLocation::Position);
		//OpenGL::DisableVertexAttribArray((u32)AttribLocation::TexCoord);
		//OpenGL::DisableVertexAttribArray((u32)AttribLocation::Colour);
	}

	void destroy(Mesh& mesh)
	{
		OpenGL::DeleteBuffers(1, &mesh.vbo);
		OpenGL::DeleteBuffers(1, &mesh.ibo);
	}
}
