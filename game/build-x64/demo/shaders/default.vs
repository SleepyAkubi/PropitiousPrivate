#version 120

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

attribute vec3 a_position;
attribute vec2 a_texCoord;
attribute vec3 a_colour;
attribute vec3 a_normal;

varying vec3 v_position;
varying vec3 v_colour;
varying vec2 v_texCoord;
varying vec3 v_normal;

uniform mat4 u_camera;
uniform Transform u_transform; //= {vec3(0), vec4(0, 0, 0, 1), vec3(1)};

void main()
{
	v_texCoord = a_texCoord.st;
	v_colour = a_colour;
	v_normal = a_normal;

	// v' = proj * view * transform * v;
	v_position = a_position;
	v_position = u_transform.position + quaternionRotate(u_transform.orientation, u_transform.scale * v_position);
	gl_Position = u_camera * vec4(v_position, 1.0);
}
