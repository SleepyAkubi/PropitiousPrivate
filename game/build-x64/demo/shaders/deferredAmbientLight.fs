#version 120

#include <common.sp>
#include <lighting.sp>

uniform BaseLight u_light;

void main()
{
  gl_FragColor = vec4(u_light.intensities, 1.0);
}
