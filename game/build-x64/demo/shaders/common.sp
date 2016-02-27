#ifndef COMMON_SP
#define COMMON_SP

vec3 calculatePosition(vec2 st, float w, float depth, mat4 inverseMatrix)
{
  // Get some homogeneous coordinates.
  float x_hs = 2.0 * st.x  - 1.0;
  float y_hs = 2.0 * st.y  - 1.0;
  float z_hs = 2.0 * depth - 1.0;

  // Normalize this vector in homogeneous space.
  vec4 position_hs = vec4(x_hs, y_hs, z_hs, 1.0) / w;

  // Take this to world space.
  vec4 position_ws = inverseMatrix * position_hs;

  // Normalize this again!
  return position_ws.xyz / position_ws.w;
}

vec4 conjugate(vec4 q)
{
	return vec4(-q.xyz, q.w);
}

float square(float x)
{
  return x;
}

struct Transform
{
	vec3 position;
	vec4 orientation;
	vec3 scale;
};

vec3 quaternionRotate(vec4 q, vec3 v)
{
	vec3 t = 2.0 * cross(q.xyz, v);
	return (v + q.w * t + cross(q.xyz, t));
}

#endif
