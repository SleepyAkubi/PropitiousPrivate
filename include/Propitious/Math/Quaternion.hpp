#ifndef PROPITIOUS_MATH_QUATERNION_HPP
#define PROPITIOUS_MATH_QUATERNION_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Angle.hpp>
#include <ostream>

namespace Propitious
{
	struct Matrix4;
	union Vector3;

	struct PROPITIOUS_EXPORT EulerAngles
	{
			Radian pitch;
			Radian yaw;
			Radian roll;
	};

	union PROPITIOUS_EXPORT Quaternion
	{
		struct
		{
			f32 x, y, z, w;
		};
		f32 data[4];
	};

	PROPITIOUS_EXPORT Quaternion operator-(const Quaternion& quaternion);

	PROPITIOUS_EXPORT Quaternion operator+(const Quaternion& a, const Quaternion& b);

	PROPITIOUS_EXPORT Quaternion operator-(const Quaternion& a, const Quaternion& b);

	PROPITIOUS_EXPORT Quaternion operator*(const Quaternion& a, const Quaternion& b);

	PROPITIOUS_EXPORT Quaternion operator*(const Quaternion& quaternion, f32 s);

	PROPITIOUS_EXPORT Quaternion operator/(const Quaternion& quaternion, f32 s);

	PROPITIOUS_EXPORT b8 operator==(const Quaternion& a, const Quaternion& b);

	PROPITIOUS_EXPORT b8 operator!=(const Quaternion& a, const Quaternion& b);

	PROPITIOUS_EXPORT Vector3 vector(const Quaternion& quaternion);

	PROPITIOUS_EXPORT f32 scalar(const Quaternion& quaternion);

	PROPITIOUS_EXPORT f32 lengthSquared(const Quaternion& quaternion);

	PROPITIOUS_EXPORT f32 length(const Quaternion& quaternion);

	PROPITIOUS_EXPORT Quaternion operator*(f32 s, const Quaternion& q);

	PROPITIOUS_EXPORT f32 dot(const Quaternion& a, const Quaternion& b);

	PROPITIOUS_EXPORT Quaternion cross(const Quaternion& a, const Quaternion& b);

	PROPITIOUS_EXPORT Quaternion normalize(const Quaternion& q);

	PROPITIOUS_EXPORT Quaternion conjugate(const Quaternion& q);

	PROPITIOUS_EXPORT Quaternion inverse(const Quaternion& q);

	PROPITIOUS_EXPORT Vector3 operator*(const Quaternion& q, const Vector3& v);

	PROPITIOUS_EXPORT std::ostream& operator<<(std::ostream& os, const Quaternion& q);

	PROPITIOUS_EXPORT Radian angle(const Quaternion q);

	PROPITIOUS_EXPORT Vector3 axis(const Quaternion& q);

	PROPITIOUS_EXPORT Quaternion angleAxis(const Radian& angle, const Vector3& axis);

	PROPITIOUS_EXPORT Radian pitch(const Quaternion& q);

	PROPITIOUS_EXPORT Radian yaw(const Quaternion& q);

	PROPITIOUS_EXPORT  Radian roll(const Quaternion& q);

	PROPITIOUS_EXPORT EulerAngles quaternionToEulerAngles(const Quaternion& q);

	PROPITIOUS_EXPORT Quaternion matrix4ToQuaternion(const Matrix4& m);

	PROPITIOUS_EXPORT Matrix4 quaternionToMatrix4(const Quaternion& q);
}

#endif
