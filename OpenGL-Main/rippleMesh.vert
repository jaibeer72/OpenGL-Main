#version 330 core
layout(location=0) in vec3 vVertex;
uniform mat4 MVP;
uniform float time;
const float amplitude = 1;
const float frequency = 1;
const float PI = 1;
void main()
{ 
  float distance = length(vVertex);
  float y = amplitude*sin(-PI*distance*frequency+time);
  gl_Position = MVP*vec4(vVertex.x, y, vVertex.z,1);
}