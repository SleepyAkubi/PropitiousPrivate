#include <Propitious/Math/Vector2.hpp>
#include <Propitious/Math/Vector3.hpp>
#include <Propitious/Math/Vector4.hpp>

namespace Propitious
{
  Vector3 operator-(const Vector3& vector) { return Vector3{-vector.x, -vector.y, -vector.z}; }

  b8 operator==(const Vector3& a, const Vector3& b)
  {
	for (usize i = 0; i < 3; i++)
	{
	  if (a.data[i] != b.data[i])
		return false;
	}

	return true;
  }

  b8 operator!=(const Vector3& a, const Vector3& b)
  {
	return !operator==(a, b);
  }

  Vector3 operator+(const Vector3& a, const Vector3& b)
  {
	return Vector3{a.x + b.x, a.y + b.y, a.z + b.z};
  }
  Vector3 operator-(const Vector3& a, const Vector3& b)
  {
	return Vector3{a.x - b.x, a.y - b.y, a.z - b.z};
  }
  Vector3 operator*(const Vector3& vector, f32 scalar)
  {
	return Vector3{scalar * vector.x, scalar * vector.y, scalar * vector.z};
  }

  Vector3 operator*(f32 scalar, const Vector3& vector)
  {
	  return Vector3{ scalar * vector.x, scalar * vector.y, scalar * vector.z };
  }

  Vector3 operator/(const Vector3& vector, f32 scalar)
  {
	return Vector3{vector.x / scalar, vector.y / scalar, vector.z / scalar};
  }
  Vector3 operator/(f32 scalar, const Vector3& vector)
  {
	return Vector3{scalar / vector.x, scalar / vector.y, scalar / vector.z};
  }


  Vector3 operator+=(Vector3& a, const Vector3& b)
  {
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;

	return a;
  }
  Vector3 operator-=(Vector3& a, const Vector3& b)
  {
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;

	return a;
  }
  Vector3 operator*=(Vector3& vector, f32 scalar)
  {
	vector.x *= scalar;
	vector.y *= scalar;
	vector.z *= scalar;

	return vector;
  }
  Vector3 operator/=(Vector3& vector, f32 scalar)
  {
	vector.x /= scalar;
	vector.y /= scalar;
	vector.z /= scalar;

	return vector;
  }

  Vector3 operator*(const Vector3& a, const Vector3& b)
  {
	Vector3 result;
	for(usize i = 0; i < 3; i++)
	  result.data[i] = a.data[i] * b.data[i];

	return result;
  }

  Vector3 operator/(const Vector3& a, const Vector3& b)
  {
	Vector3 result;
	for(usize i = 0; i < 3; i++)
	  result.data[i] = a.data[i] / b.data[i];

	return result;
  }

  // EXTRAS

	f32 dot(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	Vector3 cross(const Vector3& a, const Vector3& b)
	{
		return Vector3{a.y * b.z - b.y * a.z,
						a.z * b.x - b.z * a.x,
						a.x  *b.y - b.x * a.y};
	}

	f32 lengthSquared(const Vector3& a)
	{
		return dot(a, a);
	}

	f32 length(const Vector3& a)
	{
		return sqrtf(lengthSquared(a));
	}

	Vector3 normalize(const Vector3& a)
	{
		return a * (1.0f / length(a));
	}

	std::ostream& operator<<(std::ostream& os, const Vector3& v)
	{
		return os << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";
	}
}
