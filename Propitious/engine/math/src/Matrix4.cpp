#include <Propitious/Math/Matrix4.hpp>
#include <Propitious/Math/Vector4.hpp>

namespace Propitious
{
	const Matrix4 Matrix4Identity =
	{
		Vector4{ 1, 0, 0, 0 },
		Vector4{ 0, 1, 0, 0 },
		Vector4{ 0, 0, 1, 0 },
		Vector4{ 0, 0, 0, 1 }
	};

	bool operator==(const Matrix4& a, const Matrix4& b)
	{
		for (usize i = 0; i < 4; i++)
		{
			if (a.data[i] != b.data[i])
				return false;
		}
		return true;
	}

	bool operator!=(const Matrix4& a, const Matrix4& b)
	{
		return !operator==(a, b);
	}

	Matrix4 operator+(const Matrix4& a, const Matrix4& b)
	{
		Matrix4 mat;
		for (usize i = 0; i < 4; i++)
			mat.data[i] = a.data[i] + b.data[i];
		return mat;
	}

	Matrix4 operator-(const Matrix4& a, const Matrix4& b)
	{
		Matrix4 mat;
		for (usize i = 0; i < 4; i++)
			mat.data[i] = a.data[i] - b.data[i];
		return mat;
	}

	Matrix4 operator*(const Matrix4& a, const Matrix4& b)
	{
		const Vector4 srcA0 = a.data[0];
		const Vector4 srcA1 = a.data[1];
		const Vector4 srcA2 = a.data[2];
		const Vector4 srcA3 = a.data[3];

		const Vector4 srcB0 = b.data[0];
		const Vector4 srcB1 = b.data[1];
		const Vector4 srcB2 = b.data[2];
		const Vector4 srcB3 = b.data[3];

		Matrix4 result;
		result.data[0] = srcA0 * srcB0.data[0] + srcA1 * srcB0.data[1] + srcA2 * srcB0.data[2] +
			srcA3 * srcB0.data[3];
		result.data[1] = srcA0 * srcB1.data[0] + srcA1 * srcB1.data[1] + srcA2 * srcB1.data[2] +
			srcA3 * srcB1.data[3];
		result.data[2] = srcA0 * srcB2.data[0] + srcA1 * srcB2.data[1] + srcA2 * srcB2.data[2] +
			srcA3 * srcB2.data[3];
		result.data[3] = srcA0 * srcB3.data[0] + srcA1 * srcB3.data[1] + srcA2 * srcB3.data[2] +
			srcA3 * srcB3.data[3];
		return result;
	}

	Vector4 operator*(const Matrix4& matrix, const Vector4& vector)
	{
		const Vector4 mul0 = matrix.data[0] * vector.data[0];
		const Vector4 mul1 = matrix.data[1] * vector.data[1];
		const Vector4 mul2 = matrix.data[2] * vector.data[2];
		const Vector4 mul3 = matrix.data[3] * vector.data[3];

		const Vector4 add0 = mul0 + mul1;
		const Vector4 add1 = mul2 + mul3;

		return add0 + add1;
	}

	Vector4 operator*(const Vector4& vector, const Matrix4& matrix)
	{
		const Vector4 mul0 = vector.data[0] * matrix.data[0];
		const Vector4 mul1 = vector.data[1] * matrix.data[1];
		const Vector4 mul2 = vector.data[2] * matrix.data[2];
		const Vector4 mul3 = vector.data[3] * matrix.data[3];

		const Vector4 add0 = mul0 + mul1;
		const Vector4 add1 = mul2 + mul3;

		return add0 + add1;
	}

	Matrix4 operator*(const Matrix4& matrix, f32 scalar)
	{
		Matrix4 mat;
		for (usize i = 0; i < 4; i++)
			mat.data[i] = matrix.data[i] * scalar;
		return mat;
	}

	Matrix4 operator/(const Matrix4& matrix, f32 scalar)
	{
		Matrix4 mat;
		for (usize i = 0; i < 4; i++)
			mat.data[i] = matrix.data[i] / scalar;
		return mat;
	}

	Matrix4 operator*(f32 scalar, const Matrix4& matrix)
	{
		Matrix4 mat;
		for (usize i = 0; i < 4; i++)
			mat.data[i] = scalar * matrix.data[i];
		return mat;
	}

	Matrix4 operator/(f32 scalar, const Matrix4& matrix)
	{
		/*Matrix4 mat;
		for (usize i = 0; i < 4; i++)
		  mat.data[i] = scalar / matrix.data[i];
		return mat;*/

		return operator/(matrix, scalar);
	}


	Matrix4& operator+=(Matrix4& a, const Matrix4& b)
	{
		return a = a + b;
	}

	Matrix4& operator-=(Matrix4& a, const Matrix4& b)
	{
		return a = a - b;
	}

	Matrix4& operator*=(Matrix4& a, const Matrix4& b)
	{
		return a = a * b;
	}

	Matrix4 transpose(const Matrix4& m)
	{
		Matrix4 result;

		for (usize i = 0; i < 4; i++)
		{
			for (usize j{ 0 }; j < 4; j++)
				result.data[i].data[j] = m.data[j].data[i];
		}
		return result;
	}

	f32 determinant(const Matrix4& m)
	{

		f32 coef00{ m.data[2].data[2] * m.data[3].data[3] - m.data[3].data[2] * m.data[2].data[3] };
		f32 coef02{ m.data[1].data[2] * m.data[3].data[3] - m.data[3].data[2] * m.data[1].data[3] };
		f32 coef03{ m.data[1].data[2] * m.data[2].data[3] - m.data[2].data[2] * m.data[1].data[3] };

		f32 coef04{ m.data[2].data[1] * m.data[3].data[3] - m.data[3].data[1] * m.data[2].data[3] };
		f32 coef06{ m.data[1].data[1] * m.data[3].data[3] - m.data[3].data[1] * m.data[1].data[3] };
		f32 coef07{ m.data[1].data[1] * m.data[2].data[3] - m.data[2].data[1] * m.data[1].data[3] };

		f32 coef08{ m.data[2].data[1] * m.data[3].data[2] - m.data[3].data[1] * m.data[2].data[2] };
		f32 coef10{ m.data[1].data[1] * m.data[3].data[2] - m.data[3].data[1] * m.data[1].data[2] };
		f32 coef11{ m.data[1].data[1] * m.data[2].data[2] - m.data[2].data[1] * m.data[1].data[2] };

		f32 coef12{ m.data[2].data[0] * m.data[3].data[3] - m.data[3].data[0] * m.data[2].data[3] };
		f32 coef14{ m.data[1].data[0] * m.data[3].data[3] - m.data[3].data[0] * m.data[1].data[3] };
		f32 coef15{ m.data[1].data[0] * m.data[2].data[3] - m.data[2].data[0] * m.data[1].data[3] };

		f32 coef16{ m.data[2].data[0] * m.data[3].data[2] - m.data[3].data[0] * m.data[2].data[2] };
		f32 coef18{ m.data[1].data[0] * m.data[3].data[2] - m.data[3].data[0] * m.data[1].data[2] };
		f32 coef19{ m.data[1].data[0] * m.data[2].data[2] - m.data[2].data[0] * m.data[1].data[2] };

		f32 coef20{ m.data[2].data[0] * m.data[3].data[1] - m.data[3].data[0] * m.data[2].data[1] };
		f32 coef22{ m.data[1].data[0] * m.data[3].data[1] - m.data[3].data[0] * m.data[1].data[1] };
		f32 coef23{ m.data[1].data[0] * m.data[2].data[1] - m.data[2].data[0] * m.data[1].data[1] };

		Vector4 fac0{ coef00, coef00, coef02, coef03 };
		Vector4 fac1{ coef04, coef04, coef06, coef07 };
		Vector4 fac2{ coef08, coef08, coef10, coef11 };
		Vector4 fac3{ coef12, coef12, coef14, coef15 };
		Vector4 fac4{ coef16, coef16, coef18, coef19 };
		Vector4 fac5{ coef20, coef20, coef22, coef23 };

		Vector4 vec0{ m.data[1].data[0], m.data[0].data[0], m.data[0].data[0], m.data[0].data[0] };
		Vector4 vec1{ m.data[1].data[1], m.data[0].data[1], m.data[0].data[1], m.data[0].data[1] };
		Vector4 vec2{ m.data[1].data[2], m.data[0].data[2], m.data[0].data[2], m.data[0].data[2] };
		Vector4 vec3{ m.data[1].data[3], m.data[0].data[3], m.data[0].data[3], m.data[0].data[3] };

		Vector4 inv0 = vec1 * fac0 - vec2 * fac1 + vec3 * fac2;
		Vector4 inv1 = vec0 * fac0 - vec2 * fac3 + vec3 * fac4;
		Vector4 inv2 = vec0 * fac1 - vec1 * fac3 + vec3 * fac5;
		Vector4 inv3 = vec0 * fac2 - vec1 * fac4 + vec2 * fac5;

		Vector4 signA{ +1, -1, +1, -1 };
		Vector4 signB{ -1, +1, -1, +1 };
		Matrix4 inverse{ inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB };

		Vector4 row0{ inverse.data[0].data[0], inverse.data[1].data[0], inverse.data[2].data[0], inverse.data[3].data[0] };

		Vector4 dot0 = m.data[0] * row0;
		f32 dot1{ (dot0.x + dot0.y) + (dot0.z + dot0.w) };
		return dot1;
	}

	Matrix4 inverse(const Matrix4& m)
	{
		f32 coef00{ m.data[2].data[2] * m.data[3].data[3] - m.data[3].data[2] * m.data[2].data[3] };
		f32 coef02{ m.data[1].data[2] * m.data[3].data[3] - m.data[3].data[2] * m.data[1].data[3] };
		f32 coef03{ m.data[1].data[2] * m.data[2].data[3] - m.data[2].data[2] * m.data[1].data[3] };
		f32 coef04{ m.data[2].data[1] * m.data[3].data[3] - m.data[3].data[1] * m.data[2].data[3] };
		f32 coef06{ m.data[1].data[1] * m.data[3].data[3] - m.data[3].data[1] * m.data[1].data[3] };
		f32 coef07{ m.data[1].data[1] * m.data[2].data[3] - m.data[2].data[1] * m.data[1].data[3] };
		f32 coef08{ m.data[2].data[1] * m.data[3].data[2] - m.data[3].data[1] * m.data[2].data[2] };
		f32 coef10{ m.data[1].data[1] * m.data[3].data[2] - m.data[3].data[1] * m.data[1].data[2] };
		f32 coef11{ m.data[1].data[1] * m.data[2].data[2] - m.data[2].data[1] * m.data[1].data[2] };
		f32 coef12{ m.data[2].data[0] * m.data[3].data[3] - m.data[3].data[0] * m.data[2].data[3] };
		f32 coef14{ m.data[1].data[0] * m.data[3].data[3] - m.data[3].data[0] * m.data[1].data[3] };
		f32 coef15{ m.data[1].data[0] * m.data[2].data[3] - m.data[2].data[0] * m.data[1].data[3] };
		f32 coef16{ m.data[2].data[0] * m.data[3].data[2] - m.data[3].data[0] * m.data[2].data[2] };
		f32 coef18{ m.data[1].data[0] * m.data[3].data[2] - m.data[3].data[0] * m.data[1].data[2] };
		f32 coef19{ m.data[1].data[0] * m.data[2].data[2] - m.data[2].data[0] * m.data[1].data[2] };
		f32 coef20{ m.data[2].data[0] * m.data[3].data[1] - m.data[3].data[0] * m.data[2].data[1] };
		f32 coef22{ m.data[1].data[0] * m.data[3].data[1] - m.data[3].data[0] * m.data[1].data[1] };
		f32 coef23{ m.data[1].data[0] * m.data[2].data[1] - m.data[2].data[0] * m.data[1].data[1] };

		Vector4 fac0{ coef00, coef00, coef02, coef03 };
		Vector4 fac1{ coef04, coef04, coef06, coef07 };
		Vector4 fac2{ coef08, coef08, coef10, coef11 };
		Vector4 fac3{ coef12, coef12, coef14, coef15 };
		Vector4 fac4{ coef16, coef16, coef18, coef19 };
		Vector4 fac5{ coef20, coef20, coef22, coef23 };

		Vector4 vec0{ m.data[1].data[0], m.data[0].data[0], m.data[0].data[0], m.data[0].data[0] };
		Vector4 vec1{ m.data[1].data[1], m.data[0].data[1], m.data[0].data[1], m.data[0].data[1] };
		Vector4 vec2{ m.data[1].data[2], m.data[0].data[2], m.data[0].data[2], m.data[0].data[2] };
		Vector4 vec3{ m.data[1].data[3], m.data[0].data[3], m.data[0].data[3], m.data[0].data[3] };

		Vector4 inv0 = vec1 * fac0 - vec2 * fac1 + vec3 * fac2;
		Vector4 inv1 = vec0 * fac0 - vec2 * fac3 + vec3 * fac4;
		Vector4 inv2 = vec0 * fac1 - vec1 * fac3 + vec3 * fac5;
		Vector4 inv3 = vec0 * fac2 - vec1 * fac4 + vec2 * fac5;

		Vector4 signA{ +1, -1, +1, -1 };
		Vector4 signB{ -1, +1, -1, +1 };
		Matrix4 inverse{ inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB };

		Vector4 row0{ inverse.data[0].data[0], inverse.data[1].data[0], inverse.data[2].data[0], inverse.data[3].data[0] };

		Vector4 dot0 = m.data[0] * row0;
		f32 dot1{ (dot0.data[0] + dot0.data[1]) + (dot0.data[2] + dot0.data[3]) };

		f32 oneOverDeterminant{ 1.0f / dot1 };

		return inverse * oneOverDeterminant;
	}
}
