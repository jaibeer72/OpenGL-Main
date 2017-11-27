#include "OpenGL-Main.h"

OpenGLsetup::OpenGLsetup()
{
}

OpenGLsetup::~OpenGLsetup()
{
}

GLFWwindow* OpenGLsetup::CreateWindow(int Width, int Height, const char* WindowName)
{
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
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
   // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return window;
}

GLFWwindow * OpenGLsetup::PrespectiveCamera_Setup(GLFWwindow *window, int width, int height)
{
	
	glfwGetFramebufferSize(window, &width, &height);
	const float fovY = 45.0f;
	const float front = 0.1f;
	const float back = 128.0f;
	GLfloat alpha = 210.0f, beta = -70.0f, zoom = 2.0f;
	float ratio = 1.0f;
	if (height > 0)
		ratio = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const double DEG2RAD = M_PI / 180;
  // tangent of half fovY
  double tangent = tan(fovY/2 * DEG2RAD);  
  // half height of near plane
  double height_f = front * tangent;     
  // half width of near plane
  double width_f = height_f * ratio;   

  //Create the projection matrix based on the near clipping 
  //plane and the location of the corners
  glFrustum(-width_f, width_f, -height_f, height_f, front, back);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -2.0);
  // rotate by beta degrees around the x-axis
  glRotatef(beta, 1.0, 0.0, 0.0);
  // rotate by alpha degrees around the z-axis
  glRotatef(alpha, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	return window;
}


