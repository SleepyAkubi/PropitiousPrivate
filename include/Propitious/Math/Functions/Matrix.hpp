#ifndef PROPITIOUS_MATH_FUNCTIONS_HPP
#define PROPITIOUS_MATH_FUNCTIONS_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Angle.hpp>

namespace Propitious
{
	union Vector3;
	struct Matrix4;

	propexp Matrix4 translate(const Vector3& v);
	// Angle in Radians
	propexp Matrix4 rotate(const Radian& angle, const Vector3& v);
	propexp Matrix4 scale(const Vector3& v);

	propexp Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top);
	propexp Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar);

	// Angle in Radians
	propexp Matrix4 perspective(const Radian& fovy, f32 aspect, f32 zNear, f32 zFar);
	propexp Matrix4 infinitePerspective(const Radian& fovy, f32 aspect, f32 zNear);

	propexp Matrix4 lookAt(const Vector3& eye, const Vector3& centre, const Vector3& up);
}

#endif
