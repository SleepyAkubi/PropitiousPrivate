#ifndef PROPITIOUS_MATH_VECTOR2_HPP
#define PROPITIOUS_MATH_VECTOR2_HPP

#include <Propitious/Common.hpp>

namespace Propitious
{
	union propexp Vector2
	{
		struct
		{
			f32 x, y;
		};
		struct
		{
			f32 r, g;
		};
		struct
		{
			f32 s, t;
		};
		f32 data[2];
	};

	propexp b8 operator==(const Vector2& a, const Vector2& b);
	propexp b8 operator!=(const Vector2& a, const Vector2& b);

	propexp Vector2 operator-(const Vector2& vector);

	propexp Vector2 operator+(const Vector2& a, const Vector2& b);
	propexp Vector2 operator-(const Vector2& a, const Vector2& b);

	propexp Vector2 operator*(const Vector2& vector, f32 scalar);

	propexp Vector2 operator/(f32 scalar, const Vector2& vector);
	propexp Vector2 operator/(Vector2& vector, f32 scalar);

	propexp Vector2 operator+=(Vector2& a, const Vector2& b);
	propexp Vector2 operator-=(Vector2& a, const Vector2& b);
	propexp Vector2 operator*=(Vector2& vector, f32 scalar);
	propexp Vector2 operator/=(Vector2& vector, f32 scalar);

	propexp Vector2 operator*(const Vector2& a, const Vector2& b);
	propexp Vector2 operator/(const Vector2& a, const Vector2& b);

	propexp f32 dot(const Vector2& a, const Vector2& b);
	propexp f32 cross(const Vector2& a, const Vector2& b);

	propexp f32 lengthSquared(const Vector2& vector);
	propexp f32 length(const Vector2& vector);

	propexp Vector2 normalize(const Vector2& vector);

	propexp std::ostream& operator<<(std::ostream& os, const Vector2& vector);
}

#endif
