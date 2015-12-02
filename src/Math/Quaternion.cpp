#include <Propitious/Math/Quaternion.hpp>

#include <Propitious/Math/Vector3.hpp>
#include <Propitious/Math/Matrix4.hpp>
#include <Propitious/Math/Constants.hpp>
#include <Propitious/Math/Functions/Trivial.hpp>

namespace Propitious {
	const Quaternion Quaternion::Identity = Quaternion{ 0, 0, 0, 1 };
	Quaternion operator-(const Quaternion& quaternion)
	{
		Quaternion c;
		c.w = -quaternion.w;
		c.x = -quaternion.x;
		c.y = -quaternion.y;
		c.z = -quaternion.z;
		return c;
	}

	Quaternion operator+(const Quaternion& a, const Quaternion& b)
	{
		Quaternion c;
		c.w = a.w + b.w;
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		c.z = a.z + b.z;

		return c;
	}

	Quaternion operator-(const Quaternion& a, const Quaternion& b)
	{
		Quaternion c;
		c.w = a.w - b.w;
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		c.z = a.z - b.z;

		return c;
	}

	Quaternion operator*(const Quaternion& a, const Quaternion& b)
	{
		Quaternion c;

		c.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
		c.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
		c.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
		c.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;

		return c;
	}

	Quaternion operator*(const Quaternion& quaternion, f32 s)
	{
		Quaternion c;
		c.x = quaternion.x * s;
		c.y = quaternion.y * s;
		c.z = quaternion.z * s;
		c.w = quaternion.w * s;

		return c;
	}

	Quaternion operator/(const Quaternion& quaternion, f32 s)
	{
		Quaternion c;
		c.x = quaternion.x / s;
		c.y = quaternion.y / s;
		c.z = quaternion.z / s;
		c.w = quaternion.w / s;

		return c;
	}

	b8 operator==(const Quaternion& a, const Quaternion& b)
	{
		for (usize i = 0; i < 4; i++)
		{
			if (a.data[i] != b.data[i])
				return false;
		}
		return true;
	}

	b8 operator!=(const Quaternion& a, const Quaternion& b)
	{
		return !operator==(a, b);
	}

	Vector3 vector(const Quaternion& quaternion) {
		Vector3 result;
		result.x = quaternion.x * quaternion.w;
		result.y = quaternion.y * quaternion.w;
		result.z = quaternion.z * quaternion.w;

		return result;
	}

	f32 scalar(const Quaternion& quaternion) { return quaternion.w; }

	f32 lengthSquared(const Quaternion& quaternion)
	{
		return quaternion.x * quaternion.x
			+ quaternion.y * quaternion.y
			+ quaternion.z * quaternion.z
			+ quaternion.w * quaternion.w;
	}

	f32 length(const Quaternion& quaternion)
	{
		return std::sqrt(lengthSquared(quaternion));
	}

	Quaternion operator*(f32 s, const Quaternion& q)
	{
		return q * s;
	}

	f32 dot(const Quaternion& a, const Quaternion& b)
	{
		return dot(vector(a), vector(b)) + a.w * b.w;
	}

	Quaternion cross(const Quaternion& a, const Quaternion& b)
	{
		return Quaternion{ a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
						  a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
						  a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
						  a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z };
	}

	Quaternion normalize(const Quaternion& q)
	{
		return q * (1.0f / length(q));
	}

	Quaternion conjugate(const Quaternion& q)
	{
		Vector3 vec = vector(-q);
		Quaternion c{ vec.x, vec.y, vec.z, q.w };
		return c;
	}

	Quaternion inverse(const Quaternion& q)
	{
		Quaternion c = conjugate(q) / dot(q, q);
		return c;
	}

	Vector3 operator*(const Quaternion& q, const Vector3& v)
	{
		Vector3 t = 2.0f * cross(vector(q), v);
		return (v + q.w * t + cross(vector(q), t));
	}

	std::ostream& operator<<(std::ostream& os, const Quaternion& q)
	{
		os << "Quaternion(";
		for (usize i = 0; i < 4; i++)
		{
			os << q.data[i];
			if (i < 3)
				os << ", ";
		}
		os << ")";
		return os;
	}

	Radian angle(const Quaternion q)
	{
		return 2.0f * Math::acos(q.w);
	}

	Vector3 axis(const Quaternion& q)
	{
		f32 tmp1 = 1.0f - q.w * q.w;
		if (tmp1 <= 0.0f)
			return Vector3{ 0,0,1 };

		f32 tmp2 = 1.0f / Math::sqrt(tmp1);

		return vector(q) * tmp2;
	}

	Quaternion angleAxis(const Radian& angle, const Vector3& axis)
	{
		Quaternion q;

		const Vector3 a = normalize(axis);
		const f32 s = Math::sin(0.5f * angle);

		vector(q) = a * s;
		q.w = Math::cos(0.5 * angle);

		return q;
	}

	Radian pitch(const Quaternion& q)
	{
		return Math::atan2(2.0f * q.data[1] * q.data[2] + q.data[3] * q.data[0],
			q.data[3] * q.data[3] - q.data[0] * q.data[0] - q.data[1] * q.data[1] + q.data[2] * q.data[2]);
	}

	Radian yaw(const Quaternion& q)
	{
		return Math::asin(-2.0f * (q.data[0] * q.data[2] - q.data[3] * q.data[1]));
	}

	Radian roll(const Quaternion& q)
	{
		return Math::atan2(2.0f * q.data[0] * q.data[1] + q.data[2] * q.data[3],
			q.data[0] * q.data[0] + q.data[3] * q.data[3] - q.data[1] * q.data[1] - q.data[2] * q.data[2]);
	}

	EulerAngles quaternionToEulerAngles(const Quaternion& q)
	{
		return{ pitch(q), yaw(q), roll(q) };
	}

	Quaternion matrix4ToQuaternion(const Matrix4& m)
	{
		f32 fourXSquaredMinus1 = m.data[0].data[0] - m.data[1].data[1] - m.data[2].data[2];
		f32 fourYSquaredMinus1 = m.data[1].data[1] - m.data[0].data[0] - m.data[2].data[2];
		f32 fourZSquaredMinus1 = m.data[2].data[2] - m.data[0].data[0] - m.data[1].data[1];
		f32 fourWSquaredMinus1 = m.data[0].data[0] + m.data[1].data[1] + m.data[2].data[2];

		int biggestIndex = 0;
		f32 fourBiggestSquaredMinus1 = fourWSquaredMinus1;

		if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}

		if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}

		if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		f32 biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
		f32 mult = 0.25f / biggestVal;


		Quaternion q;
		switch (biggestIndex)
		{
		case 0:
		{
			q.w = biggestVal;
			q.x = (m.data[1].data[2] - m.data[2].data[1]) * mult;
			q.y = (m.data[2].data[0] - m.data[0].data[2]) * mult;
			q.z = (m.data[0].data[1] - m.data[1].data[0]) * mult;
			break;
		}
		case 1:
		{
			q.w = (m.data[1].data[2] - m.data[2].data[1]) * mult;
			q.x = biggestVal;
			q.y = (m.data[0].data[1] + m.data[1].data[0]) * mult;
			q.z = (m.data[2].data[0] + m.data[0].data[2]) * mult;
			break;
		}
		case 2:
		{
			q.w = (m.data[2].data[0] - m.data[0].data[2]) * mult;
			q.x = (m.data[0].data[1] + m.data[1].data[0]) * mult;
			q.y = biggestVal;
			q.z = (m.data[1].data[2] + m.data[2].data[1]) * mult;
			break;
		}
		case 3:
		{
			q.w = (m.data[0].data[1] - m.data[1].data[0]) * mult;
			q.x = (m.data[2].data[0] + m.data[0].data[2]) * mult;
			q.y = (m.data[1].data[2] + m.data[2].data[1]) * mult;
			q.z = biggestVal;
			break;
		}
		default:
		{
			assert(false);
			break;
		}
		}

		return q;
	}

	Matrix4 quaternionToMatrix4(const Quaternion& q)
	{
		Matrix4 mat = Matrix4::Identity;
		Quaternion a = normalize(q);

		const f32 xx = a.x * a.x;
		const f32 yy = a.y * a.y;
		const f32 zz = a.z * a.z;

		const f32 xy = a.x * a.y;
		const f32 xz = a.x * a.z;

		const f32 yz = a.y * a.z;

		const f32 wx = a.w * a.x;
		const f32 wy = a.w * a.y;
		const f32 wz = a.w * a.z;

		mat.data[0].data[0] = 1.0f - 2.0f * (yy + zz);
		mat.data[0].data[1] = 2.0f * (xy + wz);
		mat.data[0].data[2] = 2.0f * (xz - wy);

		mat.data[1].data[0] = 2.0f * (xy - wz);
		mat.data[1].data[1] = 1.0f - 2.0f * (xx + zz);
		mat.data[1].data[2] = 2.0f * (yz + wx);

		mat.data[2].data[0] = 2.0f * (xz + wy);
		mat.data[2].data[1] = 2.0f * (yz - wx);
		mat.data[2].data[2] = 1.0f - 2.0f * (xx + yy);

		return mat;
	}

	Quaternion lookAtQuaternion(const Vector3& eye, const Vector3& centre, const Vector3& up)
	{
		const f32 similar = 0.001f;

		if (length(centre - eye) < similar)
			return Quaternion(); // You cannot look at where you are!

		return matrix4ToQuaternion(lookAtMatrix(eye, centre, up));
		/*Vector3 forwardVector = normalize(centre - eye);
		f32 dotProduct = dot({0, 0, 1}, forwardVector);
		if (std::abs(dotProduct - (-1.0f)) < 0.000001f)
		{
		return Quaternion(up.x, up.y, up.z, Constants<f32>::Pi());
		}
		if (std::abs(dotProduct - (1.0f)) < 0.000001f)
		{
		return Quaternion();
		}
		Radian rotationAngle = acos(dotProduct);
		Vector3 rotationAxis = normalize(cross({0, 0, 1}, forwardVector));
		return angleAxis(rotationAngle, rotationAxis);*/
	}
}
