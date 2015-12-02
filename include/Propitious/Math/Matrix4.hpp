#ifndef PROPITIOUS_MATH_MATRIX4_HPP
#define PROPITIOUS_MATH_MATRIX4_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Vector4.hpp>
#include <Propitious/Math/Vector3.hpp>

namespace Propitious
{
	struct PROPITIOUS_EXPORT Matrix4
	{
		union
		{
			struct
			{
				Vector4 x, y, z, w;
			};
			Vector4 data[4];
		};

		static const Matrix4 Identity;
	};

	PROPITIOUS_EXPORT bool operator==(const Matrix4& a, const Matrix4& b);
	PROPITIOUS_EXPORT bool operator!=(const Matrix4& a, const Matrix4& b);
	PROPITIOUS_EXPORT Matrix4 operator+(const Matrix4& a, const Matrix4& b);
	PROPITIOUS_EXPORT Matrix4 operator-(const Matrix4& a, const Matrix4& b);
	PROPITIOUS_EXPORT Matrix4 operator*(const Matrix4& a, const Matrix4& b);
	PROPITIOUS_EXPORT Vector4 operator*(const Matrix4& matrix, const Vector4& vector);
	PROPITIOUS_EXPORT Vector4 operator*(const Vector4& vector, const Matrix4& matrix);
	PROPITIOUS_EXPORT Matrix4 operator*(const Matrix4& matrix, f32 scalar);
	PROPITIOUS_EXPORT Matrix4 operator/(const Matrix4& matrix, f32 scalar);
	PROPITIOUS_EXPORT Matrix4 operator*(f32 scalar, const Matrix4& matrix);
	PROPITIOUS_EXPORT Matrix4 operator/(f32 scalar, const Matrix4& matrix);
	PROPITIOUS_EXPORT Matrix4& operator+=(Matrix4& a, const Matrix4& b);
	PROPITIOUS_EXPORT Matrix4& operator-=(Matrix4& a, const Matrix4& b);
	PROPITIOUS_EXPORT Matrix4& operator*=(Matrix4& a, const Matrix4& b);

	PROPITIOUS_EXPORT Matrix4 transpose(const Matrix4& m);
	PROPITIOUS_EXPORT f32 determinant(const Matrix4& m);
	PROPITIOUS_EXPORT Matrix4 inverse(const Matrix4& m);

	PROPITIOUS_EXPORT std::ostream& operator<<(std::ostream& os, const Matrix4& m);

	Matrix4 lookAtMatrix(const Vector3& eye, const Vector3& centre, const Vector3& up)
	{
		const Vector3 f(normalize(centre - eye));
		const Vector3 s(normalize(cross(f, up)));
		const Vector3 u(cross(s, f));

		Matrix4 result;
		result.data[0].data[0] = +s.x;
		result.data[1].data[0] = +s.y;
		result.data[2].data[0] = +s.z;

		result.data[0].data[1] = +u.x;
		result.data[1].data[1] = +u.y;
		result.data[2].data[1] = +u.z;

		result.data[0].data[2] = -f.x;
		result.data[1].data[2] = -f.y;
		result.data[2].data[2] = -f.z;

		result.data[3].data[0] = -dot(s, eye);
		result.data[3].data[1] = -dot(u, eye);
		result.data[3].data[2] = +dot(f, eye);

		return result;
	}

}

#endif
