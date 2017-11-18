#include<iostream>
#include<math.h>

// Headers and the objs 
#include"Premitives2D.h"
#include"OpenGL-Main.h"

//objs
OpenGLsetup OGL;
Prem2D prem2D;

void drawPointsDemo(int width, int height)
{
	GLfloat size = 5.0f;
	for (GLfloat x = 0.0f; x <= 1.0f; x += 0.2f, size += 5)
	{
		Vertex v1 = { x, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
		prem2D.drawPoint(v1, size);
	}
}

//Global Variables
const int Window_Width=640*2;
const int Window_Height=480;
int main() {
	GLFWwindow* window = OGL.CreateWindow(Window_Width, Window_Height, "This Is a Window Name"); 
	OGL.CheckWindowWorking(window); 
	glfwMakeContextCurrent(window);
	OGL.BasicAntiAlasing();
	//gameLoop
	while (!glfwWindowShouldClose(window))
	{
		OGL.Ortho_Projection_Setup(window, Window_Width, Window_Height);
		drawPointsDemo(5.0f, 1.0f);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}