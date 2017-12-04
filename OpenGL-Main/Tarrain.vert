#version 330 core 
layout (location=0) in vec3 vVertex;
uniform mat4 MVP;
smooth out vec4 vSmoothColor;
void main()
{
  //float height = texture(heightMapTexture, vVertex.xz).r*scale - half_scale;
  //vec2 pos  = (vVertex.xz*2.0-1)*HALF_TERRAIN_SIZE;
  vec3 color;
   if(vVertex.y < -2.5)
		color=vec3(0,0.24,1);
  if(vVertex.y > -2.5 && vVertex.y < -1.5)
		color=vec3(0,0,0.5);
  if(vVertex.y > -1.5 && vVertex.y < 0)
		color=vec3(0.2,1,0);
	if(vVertex.y > 0 && vVertex.y <0.7)
		color=vec3(1,0,0);
	if(vVertex.y > 0.7 && vVertex.y <1.5)
		color=vec3(1,1,1);
		if(vVertex.y >1.5)
		color=vec3(0.2,0,0);
 // else
	//color=vec3(1,1,1);

  vSmoothColor = vec4(color,1);
  gl_Position = MVP*vec4(vVertex, 1);
}