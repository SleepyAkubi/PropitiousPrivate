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
attribute vec3 a_tangent;

varying vec3 v_position;
varying vec3 v_position_ws;
varying vec3 v_colour;
varying vec2 v_texCoord;
varying vec3 v_normal;
varying mat3 v_tbnMatrixInv;

uniform mat4 u_camera;
uniform Transform u_transform; //= {vec3(0), vec4(0, 0, 0, 1), vec3(1)};

void main()
{
	v_position = a_position;
	v_texCoord = a_texCoord.st;
	v_colour = a_colour;

	vec3 normal  = normalize(quaternionRotate(u_transform.orientation, a_normal));
	vec3 tangent = normalize(quaternionRotate(u_transform.orientation, a_tangent));
	tangent			 = normalize(tangent - dot(tangent, normal) * normal);
	vec3 bitangent = cross(tangent, normal);

	v_tbnMatrixInv = transpose(mat3(tangent, bitangent, normal));

	vec3 pos = a_position;
	pos = u_transform.position + quaternionRotate(u_transform.orientation, u_transform.scale * pos);
	v_position_ws = pos;

	gl_Position = u_camera * vec4(pos, 1.0);
}
