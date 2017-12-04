#version 330 core 
layout (location=0) in vec3 vVertex;
layout (location = 1) in vec3 vColor;
uniform mat4 MVP;
uniform ivec2 HALF_TERRAIN_SIZE;
uniform sampler2D heightMapTexture;
uniform float scale;
uniform float half_scale;
smooth out vec4 vSmoothColor;
void main()
{
  //float height = texture(heightMapTexture, vVertex.xz).r*scale - half_scale;
  //vec2 pos  = (vVertex.xz*2.0-1)*HALF_TERRAIN_SIZE;
  vSmoothColor = vec4(vColor,1);
  gl_Position = MVP*vec4(vVertex, 1);
}