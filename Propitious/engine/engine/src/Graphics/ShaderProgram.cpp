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
	String ShaderProgram::stringFromFile(const String& filename)
	{
		std::ifstream file;
		file.open(cString(filename), std::ios::in | std::ios::binary);

		String fileDirectory = getFileDirectory(filename) + "/";

		String output;
		String line;

		Assert(file.is_open() == true)

		while (file.good())
		{
			getline(file, line);

			if (find(line, "#include") == (usize)(-1))
			{
				output = output + line + '\n';
			}
			else
			{
				u32 spaceLocation = find(line, " ") + 1;
				String includeFilename = substring(line, spaceLocation, length(line));

				if (includeFilename[0] == '<')
				{
					includeFilename = m_path + "/shaders/" + substring(includeFilename, 1, length(includeFilename) - 1);
				}
				else if (includeFilename[0] == '\"')
				{
					includeFilename = fileDirectory + substring(includeFilename, 1, length(includeFilename) - 1);
				}

				String toAppend = stringFromFile(includeFilename);
				output = output + toAppend + "\n";
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
		const String& filename)
	{
		String source = stringFromFile(filename);
		return attachShaderFromMemory(type, source);
	}

	const bool ShaderProgram::attachShaderFromMemory(ShaderType type,
		const String& source)
	{
		if (!m_object)
			m_object = OpenGL::CreateProgram();

		const char* shaderSource = unwiden(cString(source));

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
			String msg("Compile failure in shader: \n");

			i32 infoLogLength;
			OpenGL::GetShaderiv(shader, OpenGL::INFO_LOG_LENGTH, &infoLogLength);
			char* strInfoLog = new char[infoLogLength + 1];
			OpenGL::GetShaderInfoLog(shader, infoLogLength, nullptr, strInfoLog);
			msg = msg + strInfoLog;

			std::cout << strInfoLog << std::endl;

			FatalError(false, strInfoLog);
			delete[] strInfoLog;

			msg = msg + "\n";

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
				String msg("ShaderProgram linking failure: \n");

				i32 infoLogLength;
				OpenGL::GetProgramiv(m_object, OpenGL::INFO_LOG_LENGTH, &infoLogLength);
				char* strInfoLog = new char[infoLogLength + 1];
				OpenGL::GetProgramInfoLog(m_object, infoLogLength, nullptr, strInfoLog);
				msg = msg + strInfoLog;

				std::cout << strInfoLog << std::endl;
				FatalError(false, strInfoLog);

				delete[] strInfoLog;

				msg = msg + "\n";

				OpenGL::DeleteProgram(m_object);
				m_object = 0;

				m_isLinked = false;
				return m_isLinked;
			}

			m_isLinked = true;
		}

		return m_isLinked;
	}

	const void ShaderProgram::bindAttribLocation(i32 location, const String& name) const
	{
		const a8* cName = unwiden(cString(name));
		OpenGL::BindAttribLocation(m_object, location, cName);
		set(m_attribLocations, hash(cName), location);
	}

	const i32 ShaderProgram::getAttribLocation(const String& name) const
	{
		const a8* cName = unwiden(cString(name));
		auto found = get(m_attribLocations, hash(cName), (i32)-1);
		if (found != (i32)-1)
			return found;

		i32 loc = OpenGL::GetAttribLocation(m_object, cName);
		set(m_attribLocations, hash(cName), loc);
		return loc;
	}

	const i32 ShaderProgram::getUniformLocation(const String& name) const
	{
		const a8* cName = unwiden(cString(name));
		auto found = get(m_uniformLocations, hash(cName), (i32)-1);
		if (found != (i32)-1)
			return found;

		i32 loc = OpenGL::GetUniformLocation(m_object, cName);
		set(m_uniformLocations, hash(cName), loc);
		return loc;
	}

	const void ShaderProgram::setUniform(const String& name, f32 x) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform1f(loc, x);
	}

	const void ShaderProgram::setUniform(const String& name, f32 x, f32 y) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform2f(loc, x, y);
	}

	const void ShaderProgram::setUniform(const String& name, f32 x, f32 y, f32 z) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform3f(loc, x, y, z);
	}

	const void ShaderProgram::setUniform(const String& name,
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

	const void ShaderProgram::setUniform(const String& name, u32 x) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform1ui(loc, x);
	}

	const void ShaderProgram::setUniform(const String& name, i32 x) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform1i(loc, x);
	}

	const void ShaderProgram::setUniform(const String& name, b8 x) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform1i(loc, (int)x);
	}

	const void ShaderProgram::setUniform(const String& name, const Vector2& v) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform2fv(loc, 1, &v.data[0]);
	}

	const void ShaderProgram::setUniform(const String& name, const Vector3& v) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform3fv(loc, 1, &v.data[0]);
	}

	const void ShaderProgram::setUniform(const String& name, const Vector4& v) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform4fv(loc, 1, &v.data[0]);
	}

	const void ShaderProgram::setUniform(const String& name, const Matrix4& m) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::UniformMatrix4fv(loc, 1, OpenGL::FALSE_, &m.data[0].data[0]);
	}

	const void ShaderProgram::setUniform(const String& name, const Quaternion& t) const
	{
		// checkInUse();
		i32 loc = getUniformLocation(name);
		if (loc == -1)
			return;
		OpenGL::Uniform4fv(loc, 1, &t.data[0]);
	}

	const void ShaderProgram::setUniform(const String& name, const Transform& t) const
	{
		// checkInUse();

		setUniform(name + ".position", t.position);
		setUniform(name + ".orientation", t.orientation);
		setUniform(name + ".scale", t.scale);
	}

	const void ShaderProgram::setUniform(const String& name, const Colour& c) const
	{
		f32 r, g, b, a;
		r = (f32)c.r / (f32)255;
		b = (f32)c.b / (f32)255;
		g = (f32)c.g / (f32)255;
		a = (f32)c.a / (f32)255;

		setUniform(name, r, g, b, a);
	}
}