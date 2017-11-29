
// Headers and the objs 
#include"Premitives2D.h"
#include"OpenGL-Main.h"
#include"GLSLShader.h"
#include"Premitives3D.h"


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

const float SPEED = 2;
float time = 0;
const int NUM_X = 40;
const int NUM_Z = 40;
glm::vec3 vertices[(NUM_X + 1)*(NUM_Z + 1)];
const int TOTAL_INDICES = NUM_X*NUM_Z * 2 * 3;
GLushort indices[TOTAL_INDICES];
float rX = 25, rY = -40, dist = -7;
const float SIZE_X = 4; //size of plane in world space
const float SIZE_Z = 4;
const float HALF_SIZE_X = SIZE_X / 2.0f;
const float HALF_SIZE_Z = SIZE_Z / 2.0f;

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


