#include <Propitious/Math/Vector2.hpp>
#include <Propitious/Math/Vector3.hpp>
#include <Propitious/Math/Vector4.hpp>
#include <Propitious/Math/Functions/Trivial.hpp>

namespace Propitious
{

  b8 operator==(const Vector2& a, const Vector2& b)
  {
    for (usize i = 0; i < 2; i++)
    {
      if (a.data[i] != b.data[i])
        return false;
    }

    return true;
  }

  b8 operator!=(const Vector2& a, const Vector2& b)
  {
    return !operator==(a, b);
  }

  Vector2 operator-(const Vector2& vector)
  {
    return {-vector.x, -vector.y};
  }

  Vector2 operator+(const Vector2& a, const Vector2& b)
  {
    return {a.x + b.x, a.y + b.y};
  }
  Vector2 operator-(const Vector2& a, const Vector2& b)
  {
    return Vector2{a.x - b.x, a.y - b.y};
  }
  Vector2 operator*(const Vector2& vector, f32 scalar)
  {
    return Vector2{scalar * vector.x, scalar * vector.y};
  }
  Vector2 operator/(const Vector2& vector, f32 scalar)
  {
    return Vector2{vector.x / scalar, vector.y / scalar};
  }


  Vector2 operator+=(Vector2& a, const Vector2& b)
  {
    a.x += b.x;
    a.y += b.y;

    return a;
  }
  Vector2 operator-=(Vector2& a, const Vector2& b)
  {
    a.x -= b.x;
    a.y -= b.y;

    return a;
  }
  Vector2 operator*=(Vector2& vector, f32 scalar)
  {
    vector.x *= scalar;
    vector.y *= scalar;

    return vector;
  }
  Vector2 operator/=(Vector2& vector, f32 scalar)
  {
    vector.x /= scalar;
    vector.y /= scalar;

    return vector;
  }

  Vector2 operator/(f32 scalar, const Vector2& vector)
  {
	  return Vector2{ scalar / vector.x, scalar / vector.y };
  }

  Vector2 operator*(const Vector2& a, const Vector2& b)
  {
    Vector2 result;
    for(usize i = 0; i < 2; i++)
      result.data[i] = a.data[i] * b.data[i];

    return result;
  }

  Vector2 operator/(const Vector2& a, const Vector2& b)
  {
    Vector2 result;
    for(usize i = 0; i < 2; i++)
      result.data[i] = a.data[i] / b.data[i];

    return result;
  }

  // Extras

  f32 dot(const Vector2& a, const Vector2& b)
  {
	  return a.x * b.x + a.y * b.y;
  }

  f32 cross(const Vector2& a, const Vector2& b)
  {
	  return a.x * b.y - b.x * a.y;
  }

  f32 lengthSquared(const Vector2& a)
  {
	  return dot(a, a);
  }

  f32 length(const Vector2& a)
  {
	  return sqrt(lengthSquared(a));
  }

  Vector2 normalize(const Vector2& a)
  {
	  return a * (1.0f / length(a));
  }

  std::ostream& operator<<(std::ostream& os, const Vector2& v)
  {
	  return os << "Vector2 (" << v.x << ", " << v.y << ")";
  }

}
