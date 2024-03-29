#ifndef PROPITIOUS_GRAPHICS_SHADERPROGRAM_HPP
#define PROPITIOUS_GRAPHICS_SHADERPROGRAM_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Colour.hpp>
#include <Propitious/Graphics/OpenGL.hpp>
#include <Propitious/Graphics/Transform.hpp>
#include <Propitious/Math/Matrix4.hpp>
#include <Propitious/Math/Quaternion.hpp>
#include <Propitious/Math/Vector2.hpp>
#include <Propitious/Math/Vector3.hpp>
#include <Propitious/Math/Vector4.hpp>
#include <map>
#include <string>

namespace Propitious
{

	enum class PROPITIOUS_EXPORT ShaderType
	{
		Vertex,
		Fragment
	};

	//union Vector2;
	//union Vector3;
	//union Vector4;
	//struct Matrix4;
	//union Quaternion;
	struct Transform;

	struct ShaderProgram
	{

	};

	class PROPITIOUS_EXPORT ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		const bool attachShaderFromFile(ShaderType type, const std::string& filename);
		const bool attachShaderFromMemory(ShaderType type, const std::string& filename);

		const void bindAttribLocation(u32 location, const std::string& name) const;

		const i32 getAttribLocation(const std::string& name) const;
		const i32 getUniformLocation(const std::string& name) const;

		const void use() const;
		const bool isInUse() const;
		const void stopUsing() const;
		const void checkInUse() const; // if not in use, will throw a std::runtime_error

		const bool link();

		const void setUniform(const std::string& name, f32 x) const;
		const void setUniform(const std::string& name, f32 x, f32 y) const;
		const void setUniform(const std::string& name, f32 x, f32 y, f32 z) const;
		const void setUniform(const std::string& name, f32 x, f32 y, f32 z, f32 w) const;
		const void setUniform(const std::string& name, u32 x) const;
		const void setUniform(const std::string& name, i32 x) const;
		const void setUniform(const std::string& name, b8 x) const;
		const void setUniform(const std::string& name, const Vector2& v) const;
		const void setUniform(const std::string& name, const Vector3& v) const;
		const void setUniform(const std::string& name, const Vector4& v) const;
		const void setUniform(const std::string& name, const Matrix4& m) const;
		const void setUniform(const std::string& name, const Quaternion& t) const;
		const void setUniform(const std::string& name, const Transform& t) const;
		const void setUniform(const std::string& name, const Colour& c) const;

		const inline u32 getObject() const
		{
			return m_object;
		}

		const inline u32 getLinkStatus() const
		{
			return m_isLinked;
		}

		void setPath(const std::string& newPath)
		{
			m_path = newPath;
		}
	private:

		std::string stringFromFile(const std::string& filename);

		std::string m_path;
		mutable std::map<std::string, i32> m_attribLocations;
		mutable std::map<std::string, i32> m_uniformLocations;

		u32 m_object;
		b8 m_isLinked;
	};
}

#endif
