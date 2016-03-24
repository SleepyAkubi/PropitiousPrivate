#include <Propitious/Math/Vector2.hpp>
#include <Propitious/Math/Vector3.hpp>
#include <Propitious/Math/Vector4.hpp>

namespace Propitious
{

  Vector4 operator-(const Vector4& vector)
  {
    return Vector4{-vector.x, -vector.y, -vector.z, -vector.w};
  }

  b8 operator==(const Vector4& a, const Vector4& b)
  {
    for (usize i = 0; i < 4; i++)
    {
      if (a.data[i] != b.data[i])
        return false;
    }

    return true;
  }

  b8 operator!=(const Vector4& a, const Vector4& b)
  {
    return !operator==(a, b);
  }

  Vector4 operator+(const Vector4& a, const Vector4& b)
  {
    return Vector4{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
  }
  Vector4 operator-(const Vector4& a, const Vector4& b)
  {
    return Vector4{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
  }
  Vector4 operator*(const Vector4& vector, f32 scalar)
  {
    return Vector4{scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w};
  }
  Vector4 operator/(const Vector4& vector, f32 scalar)
  {
    return Vector4{vector.x / scalar, vector.y / scalar, vector.z / scalar, vector.w / scalar};
  }
  Vector4 operator/(f32 scalar, const Vector4& vector)
  {
    return Vector4{scalar / vector.x, scalar / vector.y, scalar / vector.z, scalar / vector.w};
  }

  Vector4 operator+=(Vector4& a, const Vector4& b)
  {
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;

    return a;
  }
  Vector4 operator-=(Vector4& a, const Vector4& b)
  {
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;

    return a;
  }
  Vector4 operator*=(Vector4& vector, f32 scalar)
  {
    vector.x *= scalar;
    vector.y *= scalar;
    vector.z *= scalar;
    vector.w *= scalar;

    return vector;
  }

      // Hadamard Product
  Vector4 operator*(const Vector4& a, const Vector4& b)
  {
    Vector4 result;
    for(usize i = 0; i < 4; i++)
      result.data[i] = a.data[i] * b.data[i];

    return result;
  }

  Vector4 operator/(const Vector4& a, const Vector4& b)
  {
    Vector4 result;
    for(usize i = 0; i < 4; i++)
      result.data[i] = a.data[i] / b.data[i];

    return result;
  }


  Vector4 operator/=(Vector4& vector, f32 scalar)
  {
    vector.x /= scalar;
    vector.y /= scalar;
    vector.z /= scalar;
    vector.w /= scalar;

    return vector;
  }

  Vector4 operator*(f32 scalar, const Vector4& vector)
  {
    return vector * scalar;
  }

  f32 dot(const Vector4& a, const Vector4& b)
  {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
  }

  f32 lengthSquared(const Vector4& a)
  {
    return dot(a, a);
  }

  f32 length(const Vector4& a)
  {
    return sqrt(lengthSquared(a));
  }

  Vector4 normalize(const Vector4& a)
  {
    return a * (1.0f / length(a));
  }

  std::ostream& operator<<(std::ostream& os, const Vector4& v)
  {
    return os << "Vector2 (" << v.data[0] << ", " << v.data[1] << ", " << v.data[2] << ", " << v.data[3] << ")";
  }
}
