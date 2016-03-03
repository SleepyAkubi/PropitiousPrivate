#ifndef PROPITIOUS_RESOURCE_HOLDERS_SHADERMANAGER_HPP
#define PROPITIOUS_RESOURCE_HOLDERS_SHADERMANAGER_HPP

#include <Propitious/Common.hpp>

#include <Propitious/Utility/File.hpp>

#include <Propitious/Resource/Holders/FileInsertionTemplateManager.hpp>
#include <Propitious/Resource/ResourceManager.hpp>
#include <Propitious/Graphics/ShaderProgram.hpp>

namespace Propitious
{
	class ShaderManager : public FileInsertionTemplateManager<ShaderProgram, std::string>
	{
	public:
		inline bool insertFromFiles(
			const std::string& id,
			const std::string& vertexFileName,
			const std::string& fragmentFileName,
			bool bindDefaultAttribLocations = true)
		{
			auto shaders = make_unique<ShaderProgram>();
			shaders->setPath(getPath());
			if (!shaders->attachShaderFromFile(ShaderType::Vertex, cString(getPath() + "/shaders/" + vertexFileName.c_str())))
				return false;

			if (!shaders->attachShaderFromFile(ShaderType::Fragment, cString(getPath() + "/shaders/" + fragmentFileName.c_str())))
				return false;

			if (bindDefaultAttribLocations)
			{
				shaders->bindAttribLocation((u32)AttribLocation::Position, "a_position");
				shaders->bindAttribLocation((u32)AttribLocation::TexCoord, "a_texCoord");
				shaders->bindAttribLocation((u32)AttribLocation::Colour, "a_colour");
				shaders->bindAttribLocation((u32)AttribLocation::Normal, "a_normal");
				shaders->bindAttribLocation((u32)AttribLocation::Tangent, "a_tangent");
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