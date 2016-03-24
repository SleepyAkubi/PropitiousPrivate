namespace Propitious
{
	enum class PROPITIOUS_EXPORT DrawType : i32
	{
		Points = OpenGL::POINTS,
		Lines = OpenGL::LINES,
		LineStrop = OpenGL::LINE_STRIP,
		LineLoop = OpenGL::LINE_LOOP,
		Triangles = OpenGL::TRIANGLES,
		TriangleStrip = OpenGL::TRIANGLE_STRIP,
		TriangleFan = OpenGL::TRIANGLE_FAN,
		Quads = OpenGL::QUADS
	};

	struct PROPITIOUS_EXPORT Mesh
	{
		u32 vbo;
		u32 ibo;
		DrawType drawType;
		i32 drawCount;
	};

	PROPITIOUS_EXPORT Mesh generate(const MeshData& data);

	PROPITIOUS_EXPORT void draw(const Mesh& mesh);

	PROPITIOUS_EXPORT void destroy(Mesh& mesh);
}