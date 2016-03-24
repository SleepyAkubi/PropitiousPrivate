#ifndef PROPITIOUS_MATH_FUNCTIONS_MATRIX_HPP
#define PROPITIOUS_MATH_FUNCTIONS_MATRIX_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Common.hpp>
#include <Propitious/Math/Angle.hpp>

namespace Propitious
{
	union Vector3;
	struct Matrix4;

	PROPITIOUS_MATH_EXPORT Matrix4 translate(const Vector3& v);
	// Angle in Radians
	PROPITIOUS_MATH_EXPORT Matrix4 rotate(const Radian& angle, const Vector3& v);
	PROPITIOUS_MATH_EXPORT Matrix4 scale(const Vector3& v);

	PROPITIOUS_MATH_EXPORT Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top);
	PROPITIOUS_MATH_EXPORT Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar);

	// Angle in Radians
	PROPITIOUS_MATH_EXPORT Matrix4 perspective(const Radian& fovy, f32 aspect, f32 zNear, f32 zFar);
	PROPITIOUS_MATH_EXPORT Matrix4 infinitePerspective(const Radian& fovy, f32 aspect, f32 zNear);

	PROPITIOUS_MATH_EXPORT Matrix4 lookAt(const Vector3& eye, const Vector3& centre, const Vector3& up);
}

#endif
