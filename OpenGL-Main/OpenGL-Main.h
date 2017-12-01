#pragma once
#include<GL\glew.h>
#include <GLFW\glfw3.h>
#include<iostream>

#include<string>
#include<map>
#include<vector>
//GLM
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtc\type_ptr.hpp>
#include<glm\gtx\euler_angles.hpp>

#include<SOIL.h>	
#include"GLSLShader.h"

#define _USE_MATH_DEFINES // M_PI constant
#include<math.h>// This has to be declared after the define function NO CLUE WHy . 
//objs
//#include<string>
//#include<iostream>
class OpenGLsetup
{
public:
	
	OpenGLsetup();
	~OpenGLsetup();
	//Creates Window 
	GLFWwindow* CreateWindow(int Width, int Height,const char* WindowName);
	//Checks if the window is working
	void CheckWindowWorking(GLFWwindow* window);
	//Smoothining things up I will learn the Math later.
	void BasicAntiAlasing();
	GLFWwindow* Ortho_Projection_Setup(GLFWwindow* window,int width,int height);
	GLFWwindow* PrespectiveCamera_Setup(GLFWwindow*, int width, int height);
private:
	static GLFWwindow* framebuffer_size_callback(GLFWwindow* window, int width, int height);
};