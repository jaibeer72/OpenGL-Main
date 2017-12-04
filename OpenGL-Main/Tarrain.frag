#version 330 core
 
layout (location=0) out vec4 vFragColor;	//fragment shader output
smooth in vec4 vSmoothColor;
void main()
{
	//output solid white color as fragment output
   vFragColor = vSmoothColor;
}