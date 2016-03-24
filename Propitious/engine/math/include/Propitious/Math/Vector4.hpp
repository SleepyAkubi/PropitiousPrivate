#ifndef PROPITIOUS_MATH_VECTOR4_HPP
#define PROPITIOUS_MATH_VECTOR4_HPP

#include <cmath>
#include <Propitious/Common.hpp>
#include <Propitious/Math/Common.hpp>

#include <iostream>

namespace Propitious
{
	union PROPITIOUS_MATH_EXPORT Vector4
	{
		struct
		{
			f32 x, y, z, w;
		};
		struct
		{
			f32 r, g, b, a;
		};
		struct
		{
			f32 s, t, p, q;
		};
		f32 data[4];
	};

	Vector4 operator-(const Vector4& vector);

	b8 operator==(const Vector4& a, const Vector4& b);
	b8 operator!=(const Vector4& a, const Vector4& b);

	Vector4 operator+(const Vector4& a, const Vector4& b);
	Vector4 operator-(const Vector4& a, const Vector4& b);
	Vector4 operator*(const Vector4& vector, f32 scalar);
	Vector4 operator/(const Vector4& vector, f32 scalar);

	Vector4 operator+=(Vector4& a, const Vector4& b);
	Vector4 operator-=(Vector4& a, const Vector4& b);
	Vector4 operator*=(Vector4& vector, f32 scalar);

	Vector4 operator*(const Vector4& a, const Vector4& b);
	Vector4 operator/(const Vector4& a, const Vector4& b);

	Vector4 operator/=(const Vector4 vector, f32 scalar);

	PROPITIOUS_MATH_EXPORT Vector4 operator*(f32 scalar, const Vector4& vector);

	PROPITIOUS_MATH_EXPORT f32 dot(const Vector4& a, const Vector4& b);

	PROPITIOUS_MATH_EXPORT f32 lengthSquared(const Vector4& a);
	PROPITIOUS_MATH_EXPORT f32 length(const Vector4& a);

	PROPITIOUS_MATH_EXPORT Vector4 normalize(const Vector4& a);

	PROPITIOUS_MATH_EXPORT std::ostream& operator<<(std::ostream& os, const Vector4& v);
}

#endif
