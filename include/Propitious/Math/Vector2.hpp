#ifndef PROPITIOUS_MATH_VECTOR2_HPP
#define PROPITIOUS_MATH_VECTOR2_HPP

#include <Propitious/Common.hpp>

namespace Propitious
{
	union PROPITIOUS_EXPORT Vector2
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

	PROPITIOUS_EXPORT b8 operator==(const Vector2& a, const Vector2& b);
	PROPITIOUS_EXPORT b8 operator!=(const Vector2& a, const Vector2& b);

	PROPITIOUS_EXPORT Vector2 operator-(const Vector2& vector);

	PROPITIOUS_EXPORT Vector2 operator+(const Vector2& a, const Vector2& b);
	PROPITIOUS_EXPORT Vector2 operator-(const Vector2& a, const Vector2& b);

	PROPITIOUS_EXPORT Vector2 operator*(const Vector2& vector, f32 scalar);

	PROPITIOUS_EXPORT Vector2 operator/(f32 scalar, const Vector2& vector);
	PROPITIOUS_EXPORT Vector2 operator/(Vector2& vector, f32 scalar);

	PROPITIOUS_EXPORT Vector2 operator+=(Vector2& a, const Vector2& b);
	PROPITIOUS_EXPORT Vector2 operator-=(Vector2& a, const Vector2& b);
	PROPITIOUS_EXPORT Vector2 operator*=(Vector2& vector, f32 scalar);
	PROPITIOUS_EXPORT Vector2 operator/=(Vector2& vector, f32 scalar);

	PROPITIOUS_EXPORT Vector2 operator*(const Vector2& a, const Vector2& b);
	PROPITIOUS_EXPORT Vector2 operator/(const Vector2& a, const Vector2& b);

	PROPITIOUS_EXPORT f32 dot(const Vector2& a, const Vector2& b);
	PROPITIOUS_EXPORT f32 cross(const Vector2& a, const Vector2& b);

	PROPITIOUS_EXPORT f32 lengthSquared(const Vector2& vector);
	PROPITIOUS_EXPORT f32 length(const Vector2& vector);

	PROPITIOUS_EXPORT Vector2 normalize(const Vector2& vector);

	PROPITIOUS_EXPORT std::ostream& operator<<(std::ostream& os, const Vector2& vector);
}

#endif
