#include <Propitious/Math/Functions/Matrix.hpp>
#include <Propitious/Graphics/Camera.hpp>

#include <Propitious/Math/Constants.hpp>
#include <Propitious/Math/Matrix4.hpp>
#include <Propitious/Math/Quaternion.hpp>
#include <Propitious/Math/Functions/Matrix.hpp>
#include <Propitious/Graphics/Transform.hpp>

namespace Propitious
{

	void lookAt(Camera& camera, const Vector3& position, const Vector3& up)
	{
		camera.transform.orientation = Propitious::conjugate(lookAtQuaternion(camera.transform.position, position, up));
	}

	void offsetOrientation(Camera& camera, const Radian& yaw, const Radian& pitch)
	{
		Quaternion yawRot = angleAxis(yaw, { 0, 1, 0 });
		Quaternion pitchRot = angleAxis(pitch, right(camera));

		camera.transform.orientation = yawRot * pitchRot * camera.transform.orientation;
	}

	Matrix4 projection(const Camera& camera)
	{
		if (camera.projectionType == ProjectionType::Perspective)
		{
			return Propitious::perspective(camera.fieldOfView, camera.viewportAspectRatio, camera.nearClippingPlane, camera.farClippingPlane);
		}
		else if (camera.projectionType == ProjectionType::Orthographic)
		{
			f32 distance = 0.5f * (camera.farClippingPlane - camera.nearClippingPlane);
			return Propitious::ortho(-camera.orthographicScale * camera.viewportAspectRatio, camera.orthographicScale + camera.viewportAspectRatio,
				-camera.orthographicScale, camera.orthographicScale,
				-distance, distance);
		}
		else if (camera.projectionType == ProjectionType::InfinitePerspective)
		{
			return Propitious::infinitePerspective(camera.fieldOfView, camera.viewportAspectRatio, camera.nearClippingPlane);
		}
		else
		{
			return Matrix4();
		}
	}


	Matrix4 view(const Camera& camera)
	{
		Matrix4 view = Matrix4::Identity;

		view = scale(Vector3{ 1, 1, 1 } / camera.transform.scale) *
			quaternionToMatrix4(conjugate(camera.transform.orientation)) *
			translate(-camera.transform.position);

		return view;
	}

}
