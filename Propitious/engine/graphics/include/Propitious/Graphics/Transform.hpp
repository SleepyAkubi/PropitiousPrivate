#ifndef PROPITIOUS_GRAPHICS_TRANSFORM_HPP
#define PROPITIOUS_GRAPHICS_TRANSFORM_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Common.hpp>

#include <Propitious/Math/Vector3.hpp>
#include <Propitious/Math/Quaternion.hpp>

namespace Propitious
{
	struct PROPITIOUS_GRAPHICS_EXPORT Transform
	{
		Vector3 position = Vector3{ 0, 0, 0 };
		Quaternion orientation = QuaternionIdentity;
		Vector3 scale = Vector3{ 1, 1, 1 };
	};

	inline Transform operator*(const Transform& parentSpace, const Transform& localSpace)
	{
		Transform worldSpace = Transform{};
		worldSpace.position = parentSpace.position + parentSpace.orientation * (parentSpace.scale * localSpace.position);
		worldSpace.orientation = parentSpace.orientation * localSpace.orientation;
		worldSpace.scale = parentSpace.scale * (parentSpace.orientation * localSpace.scale);

		return worldSpace;
	}

	inline Transform operator*=(Transform& parentSpace, const Transform& localSpace)
	{
		parentSpace = parentSpace * localSpace;
		return parentSpace;
	}

	inline Transform operator/(const Transform& worldSpace, const Transform& parentSpace)
	{
		Transform localSpace = Transform{};
		const Quaternion parentSpaceConjugation = conjugate(parentSpace.orientation);
		localSpace.position = (parentSpaceConjugation * (worldSpace.position - parentSpace.position)) / parentSpace.scale;
		localSpace.orientation = parentSpaceConjugation * worldSpace.orientation;
		localSpace.scale = parentSpaceConjugation * (worldSpace.scale / parentSpace.scale);

		return localSpace;
	}

	inline Transform operator/=(Transform& worldSpace, const Transform& parentSpace)
	{
		worldSpace = worldSpace / parentSpace;
		return worldSpace;
	}

	inline Vector3 transform(const Transform& transform, const Vector3& point)
	{
		return (conjugate(transform.orientation) * (transform.position - point)) / transform.scale;
	}

	Transform inverse(const Transform& transform)
	{
		const Quaternion orientationConjugate = conjugate(transform.orientation);

		Transform inverseTransform = Transform{};
		inverseTransform.position = (orientationConjugate * -transform.position) / transform.scale;
		inverseTransform.orientation = orientationConjugate;
		inverseTransform.scale = orientationConjugate * (Vector3{ 1, 1, 1 } / transform.scale);

		return inverseTransform;
	}
}

#endif