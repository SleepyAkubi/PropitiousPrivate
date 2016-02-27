#ifndef PROPITIOUS_RESOURCE_HOLDERS_MESHMANAGER_HPP
#define PROPITIOUS_RESOURCE_HOLDERS_MESHMANAGER_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Resource/Holders/FileInsertionTemplateManager.hpp>
#include <Propitious/Resource/ResourceManager.hpp>
#include <Propitious/Graphics/Mesh.hpp>
#include <fstream>

namespace Propitious
{
	class MeshManager : public FileInsertionTemplateManager<Mesh, std::string>
	{
	public:
		inline bool insertFromFile(
			const std::string& id,
			const std::string& filename)
		{
			std::ifstream file;
			std::string foo = std::string(getPath() + "/meshes/" + filename);
			file.open(foo, std::ios::in | std::ios::binary);

			if (!file.is_open())
			{
				// TODO(Preston): error handling
				return false;
			}


			std::string line;
			MeshData data;
			Array<Vector3> verticeslist;
			Array<Vector2> uvslist;
			Array<u32> vertexIndices;
			while (file.good())
			{
				getline(file, line);
				if (line[0] == 'v' && line[1] == ' ')
				{
					Vector3 vertices;
					sscanf(line.c_str(), "v %f %f %f", &vertices.x, &vertices.y, &vertices.z);
					append(verticeslist, vertices);
				}
				if (line[0] == 'v' && line[1] == 't')
				{
					Vector2 uv;
					sscanf(line.c_str(), "vt %f %f", &uv.x, &uv.y);
					append(uvslist, uv);
				}
				if (line[0] == 'f')
				{
					std::string vertex1, vertex2, vertex3;
					u32 vertexIndex[3];
					int matched = sscanf(
						line.c_str(), 
						"f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", 
						&vertexIndex[0],
						&vertexIndex[1], 
						&vertexIndex[2]);
					if (matched != 3)
					{
						int matched = sscanf(
							line.c_str(),
							"f %d//%*d %d//%*d %d//%*d",
							&vertexIndex[0],
							&vertexIndex[1],
							&vertexIndex[2]);
						if (matched != 3)
							return false;
					}

					addFace(data, vertexIndex[0], vertexIndex[1], vertexIndex[2]);
				}
			}
			for (usize i = 0; i < verticeslist.length; i++)
			{
				append(data.vertices, vertex(verticeslist[i], uvslist[i]));
			}
			data.generateNormals();
			data.drawType = DrawType::Triangles;

			std::unique_ptr<Mesh> mesh = make_unique<Mesh>();
			*mesh.get() = generate(data);

			insert(id, std::move(mesh));
		}
	};
}

#endif