#ifndef PROPITIOUS_MATH_VECTOR3_HPP
#define PROPITIOUS_MATH_VECTOR3_HPP

#include <cmath>
#include <Propitious/Common.hpp>

#include <iostream>

namespace Propitious
{
	union propexp Vector3
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

	propexp Vector3 operator-(const Vector3& vector);

	propexp b8 operator==(const Vector3& a, const Vector3& b);
	propexp b8 operator!=(const Vector3& a, const Vector3& b);

	propexp Vector3 operator+(const Vector3& a, const Vector3& b);
	propexp Vector3 operator-(const Vector3& a, const Vector3& b);
	propexp Vector3 operator*(const Vector3& vector, f32 scalar);
	propexp Vector3 operator/(const Vector3& vector, f32 scalar);

	propexp Vector3 operator+(f32 scalar, const Vector3& vector);
	propexp Vector3 operator/(f32 scalar, const Vector3& vector);

	propexp Vector3 operator+=(Vector3& a, const Vector3& b);
	propexp Vector3 operator-=(Vector3& a, const Vector3& b);
	propexp Vector3 operator*=(Vector3& vector, f32 scalar);
	propexp Vector3 operator/=(Vector3& vector, f32 scalar);

	propexp Vector3 operator*(const Vector3& a, const Vector3& b);
	propexp Vector3 operator/(const Vector3& a, const Vector3& b);

	propexp Vector3 operator*(f32 scalar, const Vector3& vector);

	propexp f32 dot(const Vector3& a, const Vector3& b);
	propexp Vector3 cross(const Vector3& a, const Vector3& b);

	propexp f32 lengthSquared(const Vector3& a);
	propexp f32 length(const Vector3& a);

	propexp Vector3 normalize(const Vector3& a);

	propexp std::ostream& operator<<(std::ostream& os, const Vector3& v);
}

#endif
