#ifndef PROPITIOUS_MATH_QUATERNION_HPP
#define PROPITIOUS_MATH_QUATERNION_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Angle.hpp>
#include <ostream>

namespace Propitious
{
	struct Matrix4;
	union Vector3;

	struct propexp EulerAngles
	{
			Radian pitch;
			Radian yaw;
			Radian roll;
	};

	union propexp Quaternion
	{
		struct
		{
			f32 x, y, z, w;
		};
		f32 data[4];
	};

	propexp Quaternion operator-(const Quaternion& quaternion);

	propexp Quaternion operator+(const Quaternion& a, const Quaternion& b);

	propexp Quaternion operator-(const Quaternion& a, const Quaternion& b);

	propexp Quaternion operator*(const Quaternion& a, const Quaternion& b);

	propexp Quaternion operator*(const Quaternion& quaternion, f32 s);

	propexp Quaternion operator/(const Quaternion& quaternion, f32 s);

	propexp b8 operator==(const Quaternion& a, const Quaternion& b);

	propexp b8 operator!=(const Quaternion& a, const Quaternion& b);

	propexp Vector3 vector(const Quaternion& quaternion);

	propexp f32 scalar(const Quaternion& quaternion);

	propexp f32 lengthSquared(const Quaternion& quaternion);

	propexp f32 length(const Quaternion& quaternion);

	propexp Quaternion operator*(f32 s, const Quaternion& q);

	propexp f32 dot(const Quaternion& a, const Quaternion& b);

	propexp Quaternion cross(const Quaternion& a, const Quaternion& b);

	propexp Quaternion normalize(const Quaternion& q);

	propexp Quaternion conjugate(const Quaternion& q);

	propexp Quaternion inverse(const Quaternion& q);

	propexp Vector3 operator*(const Quaternion& q, const Vector3& v);

	propexp std::ostream& operator<<(std::ostream& os, const Quaternion& q);

	propexp Radian angle(const Quaternion q);

	propexp Vector3 axis(const Quaternion& q);

	propexp Quaternion angleAxis(const Radian& angle, const Vector3& axis);

	propexp Radian pitch(const Quaternion& q);

	propexp Radian yaw(const Quaternion& q);

	propexp  Radian roll(const Quaternion& q);

	propexp EulerAngles quaternionToEulerAngles(const Quaternion& q);

	propexp Quaternion matrix4ToQuaternion(const Matrix4& m);

	propexp Matrix4 quaternionToMatrix4(const Quaternion& q);
}

#endif
