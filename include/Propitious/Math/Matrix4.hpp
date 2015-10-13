#ifndef PROPITIOUS_MATH_MATRIX4_HPP
#define PROPITIOUS_MATH_MATRIX4_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Vector4.hpp>

namespace Propitious
{
	struct propexp Matrix4
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

	propexp bool operator==(const Matrix4& a, const Matrix4& b);
	propexp bool operator!=(const Matrix4& a, const Matrix4& b);
	propexp Matrix4 operator+(const Matrix4& a, const Matrix4& b);
	propexp Matrix4 operator-(const Matrix4& a, const Matrix4& b);
	propexp Matrix4 operator*(const Matrix4& a, const Matrix4& b);
	propexp Vector4 operator*(const Matrix4& matrix, const Vector4& vector);
	propexp Vector4 operator*(const Vector4& vector, const Matrix4& matrix);
	propexp Matrix4 operator*(const Matrix4& matrix, f32 scalar);
	propexp Matrix4 operator/(const Matrix4& matrix, f32 scalar);
	propexp Matrix4 operator*(f32 scalar, const Matrix4& matrix);
	propexp Matrix4 operator/(f32 scalar, const Matrix4& matrix);
	propexp Matrix4& operator+=(Matrix4& a, const Matrix4& b);
	propexp Matrix4& operator-=(Matrix4& a, const Matrix4& b);
	propexp Matrix4& operator*=(Matrix4& a, const Matrix4& b);

	propexp Matrix4 transpose(const Matrix4& m);
	propexp f32 determinant(const Matrix4& m);
	propexp Matrix4 inverse(const Matrix4& m);

	propexp std::ostream& operator<<(std::ostream& os, const Matrix4& m);

}

#endif
