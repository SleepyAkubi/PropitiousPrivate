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

		glGenBuffers(1, &mesh.vbo);
		glGenBuffers(1, &mesh.ibo);

		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * length(data.vertices), &data.vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * length(data.indices), &data.indices[0], GL_STATIC_DRAW);

		return mesh;
	}

	void draw(const Mesh& mesh)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

		glVertexAttribPointer((u32)AttribLocation::Position,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex), // Stride
			(const GLvoid*)(0));
		glVertexAttribPointer((u32)AttribLocation::TexCoord,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex), // Stride
			(const GLvoid*)(sizeof(Vector3)));
		glVertexAttribPointer((u32)AttribLocation::Colour,
			4,
			GL_UNSIGNED_BYTE,
			GL_TRUE,
			sizeof(Vertex), // Stride
			(const GLvoid*)(sizeof(Vector3) + sizeof(Vector2)));
		glVertexAttribPointer((u32)AttribLocation::Normal,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex), // Stride
			(const GLvoid*)(sizeof(Vector3) + sizeof(Vector2) + sizeof(Colour)));

		glDrawElements((i32)mesh.drawType, mesh.drawCount, GL_UNSIGNED_INT, nullptr);

		//glDisableVertexAttribArray((u32)AttribLocation::Position);
		//glDisableVertexAttribArray((u32)AttribLocation::TexCoord);
		//glDisableVertexAttribArray((u32)AttribLocation::Colour);
	}

	void destroy(Mesh& mesh)
	{
		glDeleteBuffers(1, &mesh.vbo);
		glDeleteBuffers(1, &mesh.ibo);
	}
}
