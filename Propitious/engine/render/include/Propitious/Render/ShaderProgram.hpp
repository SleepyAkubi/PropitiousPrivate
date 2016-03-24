#ifndef PROPITIOUS_GRAPHICS_SHADERPROGRAM_HPP
#define PROPITIOUS_GRAPHICS_SHADERPROGRAM_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Common.hpp>

#include <Propitious/User/FileSystem.hpp>
#include <Propitious/Containers/HashMap.hpp>
#include <Propitious/Graphics/Colour.hpp>
#include <Propitious/Graphics/Transform.hpp>
#include <Propitious/Math/Matrix4.hpp>
#include <Propitious/Math/Quaternion.hpp>
#include <Propitious/Math/Vector2.hpp>
#include <Propitious/Math/Vector3.hpp>
#include <Propitious/Math/Vector4.hpp>

namespace Propitious
{

	enum class ShaderType
	{
		Vertex,
		Fragment,
		//Geometry
	};

	struct Transform;

	abstract class PROPITIOUS_GRAPHICS_EXPORT ShaderProgram
	{
	public:
		ShaderProgram(FileSystem& filesystem = defaultFileSystem())
			: filesystem(filesystem)
		{

		}
		~ShaderProgram() = default;

		const bool attachShaderFromFile(ShaderType type, const a8* filename);
		virtual const bool attachShaderFromMemory(ShaderType type, const a8* filename) = 0;

		virtual const void bindAttribLocation(i32 location, const a8* name) const = 0;

		virtual const i32 getAttribLocation(const a8* name) const = 0;
		virtual const i32 getUniformLocation(const a8* name) const = 0;

		virtual const void use() const = 0;
		virtual const bool isInUse() const = 0;
		virtual const void stopUsing() const = 0;

		virtual const bool link() = 0;

		virtual const void setUniform(const a8* name, f32 x) const = 0;
		virtual const void setUniform(const a8* name, f32 x, f32 y) const = 0;
		virtual const void setUniform(const a8* name, f32 x, f32 y, f32 z) const = 0;
		virtual const void setUniform(const a8* name, f32 x, f32 y, f32 z, f32 w) const = 0;
		virtual const void setUniform(const a8* name, u32 x) const = 0;
		virtual const void setUniform(const a8* name, i32 x) const = 0;
		virtual const void setUniform(const a8* name, b8 x) const = 0;
		virtual const void setUniform(const a8* name, const Vector2& v) const = 0;
		virtual const void setUniform(const a8* name, const Vector3& v) const = 0;
		virtual const void setUniform(const a8* name, const Vector4& v) const = 0;
		virtual const void setUniform(const a8* name, const Matrix4& m) const = 0;
		virtual const void setUniform(const a8* name, const Quaternion& t) const = 0;
		virtual const void setUniform(const a8* name, const Transform& t) const = 0;
		virtual const void setUniform(const a8* name, const Colour& c) const = 0;
	private:
		FileSystem& filesystem;
		mutable HashMap<i32> m_attribLocations;
		mutable HashMap<i32> m_uniformLocations;
		b8 m_isLinked;

	};
}

#endif
