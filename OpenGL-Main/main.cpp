
// Headers and the objs 
#include"Premitives2D.h"
#include"OpenGL-Main.h"
#include"GLSLShader.h"
#include"Premitives3D.h"
//#include"AbstractCamera.h"
#define _USE_MATH_DEFINES // M_PI constant
#include<math.h>// This has to be declared after the define function NO CLUE WHy . 

#define _USE_MATH_DEFINES // M_PI constant
#include<math.h>// This has to be declared after the define function NO CLUE WHy . 
//objs

#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);


OpenGLsetup OGL;
Prem2D prem2D; 
GLSLShader shader;
Premitives3D prem3D;
//===============================
// Demo Text Functions from the book 
//---------------------------=------

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double x, double y);
void scroll_callback(GLFWwindow* window, double x, double y);

///---------------------------------------------------------
//-------------------------------
//Global Variables
//---------------------------
const int Window_Width=1000;
const int Window_Height=1000;

//glmVertex vertices[3];
GLuint vaoID;
GLuint vboVerticesID;
GLuint vboIndicesID;
GLboolean locked = GL_FALSE;
GLfloat alpha = 210.0f, beta = -70.0f, zoom = 2.0f;
bool freeze = true;
float cursorX, cursorY; 

///------------------------------------------
//------------------------------------
// Important matrixes
//----------------------------

glm::mat4  P = glm::mat4(1); // projection Mat
glm::mat4 MV = glm::mat4(1); // Model Mat


void main() {
	GLFWwindow* window = OGL.CreateWindow(Window_Width, Window_Height, "This Is a Window Name");
  //GLFWwindow* window = OGL.CreateWindow(Window_Width, Window_Height, "This Is a Window Name");
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	OGL.CheckWindowWorking(window); 
	OGL.BasicAntiAlasing();
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Fail to Initialize GLEW\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//glfwSwapInterval(1);
	
	//start code here
	
	//keyboard input callback
	glfwSetKeyCallback(window, key_callback);


	//mouse button callback
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	//mouse movement callback
	glfwSetCursorPosCallback(window, cursor_position_callback);

	//mouse scroll callback
	glfwSetScrollCallback(window, scroll_callback);
	
	
	while (!glfwWindowShouldClose(window))
	{
		OGL.Ortho_Projection_Setup(window, Window_Width, Window_Height);
		
		//OGL.PrespectiveCamera_Setup(window, Window_Width, Window_Height); 
		
		//--------------------------
		// enter code here 
		//------------------------
		//glViewport(0, 0, (GLsizei)Window_Width, (GLsizei)Window_Height);
		//prem2D.drawTriangle(vertices[0], vertices[1], vertices[2]);
		prem3D.drawReppleMesh(5, 5); 
		//-----------------------------
		//end code 
		//------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	shader.DeleteShaderProgram();
	prem2D.deleteBufferObjs();
	prem3D.deleteBufferObjs(); 
	glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
		return;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case GLFW_KEY_SPACE:
		freeze = !freeze;
		break;
	case GLFW_KEY_LEFT:
		alpha += 5.0f;
		break;
	case GLFW_KEY_RIGHT:
		alpha -= 5.0f;
		break;
	case GLFW_KEY_UP:
		beta -= 5.0f;
		break;
	case GLFW_KEY_DOWN:
		beta += 5.0f;
		break;
	case GLFW_KEY_PAGE_UP:
		zoom -= 0.25f;
		if (zoom < 0.0f)
			zoom = 0.0f;
		break;
	case GLFW_KEY_PAGE_DOWN:
		zoom += 0.25f;
		break;
	default:
		break;
	}
}

void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	if (button != GLFW_MOUSE_BUTTON_LEFT)
		return;
	if (action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		locked = GL_TRUE;
	}
	else
	{
		locked = GL_FALSE;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void cursor_position_callback(GLFWwindow * window, double x, double y)
{
	//if the mouse button is pressed
	if (locked)
	{
		alpha += (GLfloat)(x - cursorX) / 10.0f;
		beta += (GLfloat)(y - cursorY) / 10.0f;
	}
	//update the cursor position
	cursorX = (int)x;
	cursorY = (int)y;
}
