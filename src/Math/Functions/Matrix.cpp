#include <Propitious/Math/Functions/Matrix.hpp>

#include <cassert>
#include <cmath>
#include <limits>

#include <Propitious/Math/Vector3.hpp>
#include <Propitious/Math/Matrix4.hpp>

#include <Propitious/Math/Angle.hpp>

namespace Propitious
{
	Matrix4 translate(const Vector3& v)
	{
		Matrix4 result = Matrix4::Identity;
		result.data[3] = Vector4{ v.x, v.y, v.z, 1 };
		return result;
	}

	Matrix4 hadamardProduct(const Matrix4& a, const Matrix4& b)
	{
		Matrix4 result;

		for (usize i = 0; i < 4; i++)
			result.data[i] = a.data[i] * b.data[i];

		return result;
	}


	std::ostream& operator<<(std::ostream& os, const Matrix4& m)
	{
		os << "Matrix4(";
		for (usize i = 0; i < 4; i++)
			os << "\n\t" << m.data[i];
		os << "\n)";

		return os;
	}

	// Angle in Radians
	Matrix4 rotate(const Radian& angle, const Vector3& v)
	{
		const f32 c = std::cos(static_cast<f32>(angle));
		const f32 s = std::sin(static_cast<f32>(angle));

		const Vector3 axis(normalize(v));
		const Vector3 t = (1.0f - c) * axis;

		Matrix4 rot = Matrix4::Identity;
		rot.data[0].data[0] = c + t.x * axis.x;
		rot.data[0].data[1] = 0 + t.x * axis.y + s * axis.z;
		rot.data[0].data[2] = 0 + t.x * axis.z - s * axis.y;
		rot.data[0].data[3] = 0;

		rot.data[1].data[0] = 0 + t.y * axis.x - s * axis.z;
		rot.data[1].data[1] = c + t.y * axis.y;
		rot.data[1].data[2] = 0 + t.y * axis.z + s * axis.x;
		rot.data[1].data[3] = 0;

		rot.data[2].data[0] = 0 + t.z * axis.x + s * axis.y;
		rot.data[2].data[1] = 0 + t.z * axis.y - s * axis.x;
		rot.data[2].data[2] = c + t.z * axis.z;
		rot.data[2].data[3] = 0;

		return rot;
	}

	Matrix4 scale(const Vector3& v)
	{
		Matrix4 result{
			Vector4{v.x, 0, 0, 0}, Vector4{0, v.y, 0, 0}, Vector4{0, 0, v.z, 0}, Vector4{0, 0, 0, 1} };
		return result;
	}

	Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top)
	{
		Matrix4 result = Matrix4::Identity;

		result.data[0].data[0] = 2.0f / (right - left);
		result.data[1].data[1] = 2.0f / (top - bottom);
		result.data[2].data[2] = -1.0f;
		result.data[3].data[0] = -(right + left) / (right - left);
		result.data[3].data[1] = -(top + bottom) / (top - bottom);

		return result;
	}

	Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar)
	{
		Matrix4 result = Matrix4::Identity;

		result.data[0].data[0] = 2.0f * zNear / (right - left);
		result.data[1].data[1] = 2.0f * zNear / (top - bottom);
		result.data[2].data[2] = -2.0f / (zFar - zNear);
		result.data[3].data[0] = -(right + left) / (right - left);
		result.data[3].data[1] = -(top + bottom) / (top - bottom);
		result.data[3].data[2] = -(zFar + zNear) / (zFar - zNear);

		return result;
	}

	// Angle in Radians
	Matrix4 perspective(const Radian& fovy, f32 aspect, f32 zNear, f32 zFar)
	{
		assert(std::fabs(aspect - std::numeric_limits<f32>::epsilon()) > 0.0f);

		const f32 tanHalfFovy = std::tan(static_cast<f32>(fovy) / 2.0f);

		Matrix4 result{};

		result.data[0].data[0] = 1.0f / (aspect * tanHalfFovy);
		result.data[1].data[1] = 1.0f / tanHalfFovy;
		result.data[2].data[2] = -(zFar + zNear) / (zFar - zNear);
		result.data[2].data[3] = -1.0f;
		result.data[3].data[2] = -2.0f * zFar * zNear / (zFar - zNear);

		return result;
	}

	Matrix4 infinitePerspective(const Radian& fovy, f32 aspect, f32 zNear)
	{
		//assert(std::fabs(aspect - std::numerical_limits<f32>::epsilon()) > 0.0f);

		const f32 range = std::tan(static_cast<f32>(fovy) / 2.0f) * zNear;
		const f32 left = -range * aspect;
		const f32 right = range * aspect;
		const f32 bottom = -range;
		//#define top range;

		Matrix4 result{};

		result.data[0].data[0] = (2.0f * zNear) / (right - left);
		result.data[1].data[1] = (2.0f * zNear) / (range - bottom);
		result.data[2].data[2] = -1.0f;
		result.data[2].data[3] = -1.0f;
		result.data[3].data[2] = -2.0f * zNear;

		return result;
	}
}
