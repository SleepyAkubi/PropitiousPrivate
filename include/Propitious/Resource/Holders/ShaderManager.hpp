#ifndef PROPITIOUS_RESOURCE_HOLDERS_SHADERMANAGER_HPP
#define PROPITIOUS_RESOURCE_HOLDERS_SHADERMANAGER_HPP

#include <Propitious/Common.hpp>

#include <Propitious/Utility/File.hpp>

#include <Propitious/Resource/ResourceManager.hpp>
#include <Propitious/Graphics/ShaderProgram.hpp>

namespace Propitious
{
	class ShaderManager : public ResourceManager<ShaderProgram, std::string>
	{
	public:
		inline bool insertFromFiles(
			const std::string& id,
			const std::string& vertexFileName,
			const std::string& fragmentFileName,
			bool bindDefaultAttribLocations = true)
		{
			auto shaders = make_unique<ShaderProgram>();

			std::string foo = getPathToExe() + "/shaders/" + vertexFileName;

			if (!shaders->attachShaderFromFile(ShaderType::Vertex, std::string(getPathToExe() + "/shaders/" + vertexFileName).c_str()))
				return false;

			if (!shaders->attachShaderFromFile(ShaderType::Fragment, std::string(getPathToExe() + "/shaders/" + fragmentFileName).c_str()))
				return false;

			if (bindDefaultAttribLocations)
			{
				shaders->bindAttribLocation((u32)AttribLocation::Position, "a_position");
				shaders->bindAttribLocation((u32)AttribLocation::TexCoord, "a_texCoord");
				shaders->bindAttribLocation((u32)AttribLocation::Colour, "a_colour");
				shaders->bindAttribLocation((u32)AttribLocation::Normal, "a_normal");
			}

			if (!shaders->link())
				return false;

			if (!insert(id, std::move(shaders)))
				return false;

			return true;
		}
	};
}

#endif