#ifndef PROPITIOUS_MATH_VECTOR3_HPP
#define PROPITIOUS_MATH_VECTOR3_HPP

#include <cmath>
#include <Propitious/Common.hpp>

#include <iostream>

namespace Propitious
{
	union PROPITIOUS_EXPORT Vector3
	{
		struct
		{
			f32 x, y, z;
		};
		struct
		{
			f32 r, g, b;
		};
		struct
		{
			f32 s, t, p;
		};
		f32 data[3];
	};

	PROPITIOUS_EXPORT Vector3 operator-(const Vector3& vector);

	PROPITIOUS_EXPORT b8 operator==(const Vector3& a, const Vector3& b);
	PROPITIOUS_EXPORT b8 operator!=(const Vector3& a, const Vector3& b);

	PROPITIOUS_EXPORT Vector3 operator+(const Vector3& a, const Vector3& b);
	PROPITIOUS_EXPORT Vector3 operator-(const Vector3& a, const Vector3& b);
	PROPITIOUS_EXPORT Vector3 operator*(const Vector3& vector, f32 scalar);
	PROPITIOUS_EXPORT Vector3 operator/(const Vector3& vector, f32 scalar);

	PROPITIOUS_EXPORT Vector3 operator+(f32 scalar, const Vector3& vector);
	PROPITIOUS_EXPORT Vector3 operator/(f32 scalar, const Vector3& vector);

	PROPITIOUS_EXPORT Vector3 operator+=(Vector3& a, const Vector3& b);
	PROPITIOUS_EXPORT Vector3 operator-=(Vector3& a, const Vector3& b);
	PROPITIOUS_EXPORT Vector3 operator*=(Vector3& vector, f32 scalar);
	PROPITIOUS_EXPORT Vector3 operator/=(Vector3& vector, f32 scalar);

	PROPITIOUS_EXPORT Vector3 operator*(const Vector3& a, const Vector3& b);
	PROPITIOUS_EXPORT Vector3 operator/(const Vector3& a, const Vector3& b);

	PROPITIOUS_EXPORT Vector3 operator*(f32 scalar, const Vector3& vector);

	PROPITIOUS_EXPORT f32 dot(const Vector3& a, const Vector3& b);
	PROPITIOUS_EXPORT Vector3 cross(const Vector3& a, const Vector3& b);

	PROPITIOUS_EXPORT f32 lengthSquared(const Vector3& a);
	PROPITIOUS_EXPORT f32 length(const Vector3& a);

	PROPITIOUS_EXPORT Vector3 normalize(const Vector3& a);

	PROPITIOUS_EXPORT std::ostream& operator<<(std::ostream& os, const Vector3& v);
}

#endif
