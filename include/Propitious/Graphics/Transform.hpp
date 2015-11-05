#ifndef PROPITIOUS_GRAPHICS_TRANSFORM_HPP
#define PROPITIOUS_GRAPHICS_TRANSFORM_HPP

#include <Propitious/Common.hpp>

namespace Propitious
{
	struct PROPITIOUS_EXPORT Transform
	{
		Vector3 position = Vector3{ 0, 0, 0 };
		Quaternion orientation = Quaternion::Identity;
		Vector3 scale = Vector3{ 1, 1, 1 };
	};

	inline Transform operator*(const Transform& parentSpace, const Transform& localSpace)
	{
		Transform worldSpace;
		worldSpace.position = parentSpace.position + parentSpace.orientation * (parentSpace.scale * localSpace.Position);
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
		Transform localSpace;
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

		Transform inverseTransform;
		inverseTransform.position = (orientationConjugate * -transform.position) / transform.scale;
		inverseTransform.orientation = orientationConjugate;
		inverseTrasnform.scale = orientationConjugate * (Vector3{ 1, 1, 1 } / t.scale);

		return inverseTransform;
	}
}

#endif