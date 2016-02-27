#include <Propitious/Graphics/ShaderProgram.hpp>
#include <Propitious/Graphics/Transform.hpp>
#include <Propitious/Utility/File.hpp>

#include <Propitious/Math/Vector2.hpp>
#include <Propitious/Math/Vector3.hpp>
#include <Propitious/Math/Vector4.hpp>
#include <Propitious/Math/Matrix4.hpp>
#include <Propitious/Math/Quaternion.hpp>

#include <fstream>
#include <vector>

#ifdef BGAME_SYSTEM_WINDOWS
#include <Windows.h>
#endif

namespace Propitious
{
	std::vector<std::string> split(const std::string& s, char delim)
	{
		std::vector<std::string> elems;

		const char* cstr = s.c_str();
		usize strLength = s.length();
		usize start = 0;
		usize end = 0;

		while (end <= strLength)
		{
			while (end <= strLength)
			{
				if (cstr[end] == delim)
					break;
				end++;
			}

			elems.emplace_back(s.substr(start, end - start));
			start = end + 1;
			end = start;
		}

		return elems;
	}

	static std::string stringFromFile(const std::string& filename)
	{
		std::ifstream file;
		file.open(filename.c_str(), std::ios::in | std::ios::binary);

		std::string fileDirectory = getFileDirectory(filename) + "/";

		std::string output;
		std::string line;

		if (!file.is_open())
		{
			/*bEngine::throwError("404 File not Found...",
			"You appear to be missing the file: \n"
			"\"" + filename + "\"\n\n"
			"That's a shader as well or it might be a part of one like an include or something... I'm not a mind reader you know.\n"
			"How do you expect us to display the amazing graphics we spent hours on without shaders?\n"
			"Well if that's missing, there's probably a load more gone as well...\n\n"
			"Try revalidating your game, that usually helps out here...\n"
			"If that doesn't fix it, please post on the game forums or GooOpenGL::e around, you might find a solution; either method works.\n\n"
			"All other error messages have a meaninOpenGL::ess error code so here's a bunch of random numbers that will help you with nothing:\n"
			"17637065fx00c2334\n"
			"Oh! We added some random f's, x's and c's in there just to make it more professional like the ones you get on BSoDs to make it seem scary.\n"
			"It's not actually bad so don't be afraid... Just follow the advice, yeah... That should fix it."
			);*/
		}
		else
		{
			while (file.good())
			{
				getline(file, line);

				if (line.find("#include") == std::string::npos)
				{
					output.append(line + "\n");
				}
				else
				{
					std::string includeFilename = split(line, ' ')[1];

					if (includeFilename[0] == '<')
					{
						includeFilename = getPathToExe() + "/shaders/" + includeFilename.substr(1, includeFilename.length() - 3);
					}
					else if (includeFilename[0] == '\"')
					{
						includeFilename = fileDirectory + includeFilename.substr(1, includeFilename.length() - 3);
					}

					std::string toAppend = stringFromFile(includeFilename);
					output.append(toAppend + "\n");
				}
			}
		}

		file.close();
		return output;
	}

	ShaderProgram::ShaderProgram()
		: m_object(0)
		, m_isLinked(false)
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		if (m_object)
			OpenGL::DeleteProgram(m_object);
	}

	const bool ShaderProgram::attachShaderFromFile(ShaderType type,
		const std::string& filename)
	{
		std::string source = stringFromFile(filename);
		return attachShaderFromMemory(type, source);
	}

	const bool ShaderProgram::attachShaderFromMemory(ShaderType type,
		const std::string& source)
	{
		if (!m_object)
			m_object = OpenGL::CreateProgram();

		const char* shaderSource = source.c_str();

		u32 shader;
		if (type == ShaderType::Vertex)
			shader = OpenGL::CreateShader(OpenGL::VERTEX_SHADER);
		else if (type == ShaderType::Fragment)
			shader = OpenGL::CreateShader(OpenGL::FRAGMENT_SHADER);
		else
			shader = 0;

		OpenGL::ShaderSource(shader, 1, &shaderSource, nullptr);
		OpenGL::CompileShader(shader);

		i32 status;
		OpenGL::GetShaderiv(shader, OpenGL::COMPILE_STATUS, &status);
		if (status == OpenGL::FALSE_)
		{
			std::string msg("Compile failure in shader: \n");

			i32 infoLogLength;
			OpenGL::GetShaderiv(shader, OpenGL::INFO_LOG_LENGTH, &infoLogLength);
			char* strInfoLog = new char[infoLogLength + 1];
			OpenGL::GetShaderInfoLog(shader, infoLogLength, nullptr, strInfoLog);
			msg.append(strInfoLog);

			std::cout << strInfoLog << std::endl;

			MessageBoxA(nullptr, strInfoLog, "Debug", MB_OK);
			while (true) {}
			delete[] strInfoLog;

			msg.append("\n");

			OpenGL::DeleteShader(shader);

			return false;
		}

		OpenGL::AttachShader(m_object, shader);

		return true;
	}

	const void ShaderProgram::use() const
	{
		if (!isInUse())
			OpenGL::UseProgram(m_object);
	}

	const bool ShaderProgram::isInUse() const
	{
		i32 currentProgram = 0;
		OpenGL::GetIntegerv(OpenGL::CURRENT_PROGRAM, &currentProgram);

		return (currentProgram == (i32)m_object);
	}

	const void ShaderProgram::stopUsing() const
	{
		if (isInUse())
			OpenGL::UseProgram(0);
	}

	const void ShaderProgram::checkInUse() const
	{
		//if (!isInUse())
		//	throw std::runtime_error("ShaderProgram not is use.");
	}

	const bool ShaderProgram::link()
	{
		if (!m_object)
			m_object = OpenGL::CreateProgram();

		if (!m_isLinked)
		{
			OpenGL::LinkProgram(m_object);

			i32 status;
			OpenGL::GetProgramiv(m_object, OpenGL::LINK_STATUS, &status);
			if (status == OpenGL::FALSE_)
			{
				std::string msg("ShaderProgram linking failure: \n");

				i32 infoLogLength;
				OpenGL::GetProgramiv(m_object, OpenGL::INFO_LOG_LENGTH, &infoLogLength);
				char* strInfoLog = new char[infoLogLength + 1];
				OpenGL::GetProgramInfoLog(m_object, infoLogLength, nullptr, strInfoLog);
				msg.append(strInfoLog);

				std::cout << strInfoLog << std::endl;
				MessageBoxA(0, strInfoLog, "Debug", MB_OK);
				while (true) {}

				delete[] strInfoLog;

				msg.append("\n");

				OpenGL::DeleteProgram(m_object);
				m_object = 0;

				m_isLinked = false;
				return m_isLinked;
			}

			m_isLinked = true;
		}

		return m_isLinked;
	}

	const void ShaderProgram::bindAttribLocation(u32 location, const std::string& name) const
	{
		OpenGL::BindAttribLocation(m_object, location, name.c_str());
		m_attribLocations[name] = location;
	}

	const i32 ShaderProgram::getAttribLocation(const std::string& name) const
	{
		auto found = m_attribLocations.find(name);
		if (found != m_attribLocations.end())
			return found->second;

		i32 loc = OpenGL::GetAttribLocation(m_object, name.c_str());
		m_attribLocations[name] = loc;
		return loc;
	}

	const i32 ShaderProgram::getUniformLocation(const std::string& name) const
	{
		auto found = m_uniformLocations.find(name);
		if (found != m_uniformLocations.end())
			return found->second;

		i32 loc = OpenGL::GetUniformLocation(m_object, name.c_str());
		m_uniformLocations[name] = loc;
		return loc;
	}

	const void ShaderProgram::setUniform(const std::string& name, f32 x) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform1f(loc, x);
	}

	const void ShaderProgram::setUniform(const std::string& name, f32 x, f32 y) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform2f(loc, x, y);
	}

	const void ShaderProgram::setUniform(const std::string& name, f32 x, f32 y, f32 z) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform3f(loc, x, y, z);
	}

	const void ShaderProgram::setUniform(const std::string& name,
		f32 x,
		f32 y,
		f32 z,
		f32 w) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform4f(loc, x, y, z, w);
	}

	const void ShaderProgram::setUniform(const std::string& name, u32 x) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform1ui(loc, x);
	}

	const void ShaderProgram::setUniform(const std::string& name, i32 x) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform1i(loc, x);
	}

	const void ShaderProgram::setUniform(const std::string& name, bool x) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform1i(loc, (int)x);
	}

	const void ShaderProgram::setUniform(const std::string& name, const Vector2& v) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform2fv(loc, 1, &v.data[0]);
	}

	const void ShaderProgram::setUniform(const std::string& name, const Vector3& v) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform3fv(loc, 1, &v.data[0]);
	}

	const void ShaderProgram::setUniform(const std::string& name, const Vector4& v) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform4fv(loc, 1, &v.data[0]);
	}

	const void ShaderProgram::setUniform(const std::string& name, const Matrix4& m) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::UniformMatrix4fv(loc, 1, OpenGL::FALSE_, &m.data[0].data[0]);
	}

	const void ShaderProgram::setUniform(const std::string& name, const Quaternion& t) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform4fv(loc, 1, &t.data[0]);
	}

	const void ShaderProgram::setUniform(const std::string& name, const Transform& t) const
	{
		// checkInUse();

		setUniform(name + ".position", t.position);
		setUniform(name + ".orientation", t.orientation);
		setUniform(name + ".scale", t.scale);
	}

	const void ShaderProgram::setUniform(const std::string& name, const Colour& c) const
	{
		f32 r, g, b, a;
		r = (f32)c.r / (f32)255;
		b = (f32)c.b / (f32)255;
		g = (f32)c.g / (f32)255;
		a = (f32)c.a / (f32)255;

		setUniform(name, r, g, b, a);
	}
}