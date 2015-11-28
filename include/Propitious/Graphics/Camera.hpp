#ifndef PROPITIOUS_CAMERA_HPP
#define PROPITIOUS_CAMERA_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Matrix4.hpp>
#include <Propitious/Math/Vector3.hpp>
#include <Propitious/Math/Angle.hpp>
#include <Propitious/Graphics/Transform.hpp>

namespace Propitious
{
	enum class ProjectionType
	{
		Perspective,
		InfinitePerspective,
		Orthographic
	};

	struct Camera
	{
		Transform transform = Transform{};
		Radian fieldOfView = Degree(90);
		f32 orthographicScale = 1.0f;
		f32 nearClippingPlane = 0.1f;
		f32 farClippingPlane = 2048.0f;
		f32 viewportAspectRatio = 16.0f / 9.0f;
		ProjectionType projectionType = ProjectionType::Perspective;
	};


	void lookAt(Camera& camera, const Vector3& position, const Vector3& up = { 0, 1, 0 })
	{}
}

#endif