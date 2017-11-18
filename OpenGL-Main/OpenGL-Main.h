#pragma once
#include"Premitives2D.h"
#include<string>
#include<iostream>
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
private:

};