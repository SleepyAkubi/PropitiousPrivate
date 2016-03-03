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


	PROPITIOUS_EXPORT void lookAt(Camera& camera, const Vector3& position, const Vector3& up = Vector3{ 0, 1, 0 });
	PROPITIOUS_EXPORT void offsetOrientation(Camera& camera, const Radian& yaw, const Radian& pitch);

	PROPITIOUS_EXPORT Matrix4 matrix(const Camera& camera);
	PROPITIOUS_EXPORT Matrix4 projection(const Camera& camera);
	PROPITIOUS_EXPORT Matrix4 view(const Camera& camera);

	Vector3 forward(const Camera& camera);
	Vector3 backwards(const Camera& camera);

	Vector3 right(const Camera& camera);
	Vector3 left(const Camera& camera);

	Vector3 up(const Camera& camera);
	Vector3 down(const Camera& camera);

	Vector3 position(const Camera& camera);
	Vector3& position(Camera& camera);

	inline Vector3 forward(const Camera& camera)
	{
		return camera.transform.orientation * Vector3{ 0, 0, -1 };
	}

	inline Vector3 backwards(const Camera& camera)
	{
		return camera.transform.orientation * Vector3{ 0, 0, +1 };
	}

	inline Vector3 right(const Camera& camera)
	{
		return camera.transform.orientation * Vector3{ +1, 0, 0 };
	}

	inline Vector3 left(const Camera& camera)
	{
		return camera.transform.orientation * Vector3{ -1, 0, 0 };
	}

	inline Vector3 up(const Camera& camera)
	{
		return camera.transform.orientation * Vector3{ 0, +1, 0 };
	}

	inline Vector3 down(const Camera& camera)
	{
		return camera.transform.orientation * Vector3{ 0, -1, 0 };
	}

	inline Matrix4 matrix(const Camera& camera)
	{
		return projection(camera) * view(camera);
	}

	inline Vector3 position(const Camera& camera)
	{
		return camera.transform.position;
	}

	inline Vector3& position(Camera& camera)
	{
		return camera.transform.position;
	}
}

#endif