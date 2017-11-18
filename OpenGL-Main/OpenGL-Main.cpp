#include "OpenGL-Main.h"

OpenGLsetup::OpenGLsetup()
{
}

OpenGLsetup::~OpenGLsetup()
{
}

GLFWwindow * OpenGLsetup::CreateWindow(int Width, int Height, const char* WindowName)
{
	if (!glfwInit())exit(EXIT_FAILURE);
	GLFWwindow* window = glfwCreateWindow(Width, Height, WindowName, NULL, NULL);
	return window;
}

void OpenGLsetup::CheckWindowWorking(GLFWwindow* window)
{
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
}

void OpenGLsetup::BasicAntiAlasing()
{
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLFWwindow* OpenGLsetup::Ortho_Projection_Setup(GLFWwindow * window, int width, int height)
{
	float ratio;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return window;
}


