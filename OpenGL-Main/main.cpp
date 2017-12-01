
// Headers and the objs 
#include"OpenGL-Main.h"
#include"GLSLShader.h"
//#include"Premitives3D.h"
#include"CFreeCamera.h"
#include"CTexturedPlane.h"

#define _USE_MATH_DEFINES // M_PI constant
#include<math.h>// This has to be declared after the define function NO CLUE WHy . 
//objs

#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

OpenGLsetup OGL;
GLSLShader shader;
//Premitives3D prem3D;
CFreeCamera cam; 

//When using multyple of the same kind of class :P 
//YAY pointers finally 

CTexturedPlane* checker_plane; 

//===============================
// Function Declaration
//---------------------------=------

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void filterMouseMoves(float dx, float dy);
void mouse_buttom_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void OnInit();
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	cam.SetupProjection(45, (GLfloat)width / height);
	
}
//void OnMouseDown(int button, int s, int x, int y);
///---------------------------------------------------------
//-------------------------------
//Global Variables
//---------------------------
const int Window_Width=1000;
const int Window_Height=1000;
const float MOUSE_FILTER_WEIGHT = 0.75f;
const int MOUSE_HISTORY_BUFFER_SIZE = 10;// ill figure this later
glm::vec2 mouseHistory[MOUSE_HISTORY_BUFFER_SIZE];
float mouseX = 0, mouseY = 0;

//flag to enable filtering
bool useFiltering = true;

// Camera Rotation Values
//GLfloat alpha = 210.0f, beta = -70.0f, zoom = 2.0f;


//for floating point imprecision
const float EPSILON = 0.001f;
const float EPSILON2 = EPSILON*EPSILON;
double mouse_sensitivity = 0.5;
//camera tranformation variables
int state = 0, oldX = 0, oldY = 0;
float rX = 0, rY = 0, fov = 45;
//delta time
float dt = 0;

//timing related variables
float last_time = 0, current_time = 0;



// Texture Variable 
GLuint checkerTextureID; 

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
	//glfwSwapInterval(1);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	// Keycallbacks
	glfwSetKeyCallback(window, key_callback); 
	//glfwSetMouseButtonCallback(window, mouse_buttom_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	framebuffer_size_callback(window, width, height);
		
	//start code here
	
	OnInit();
	//glm::vec3 vertices[4];
	while (!glfwWindowShouldClose(window))
	{
		
		glfwPollEvents();
		last_time = current_time;
		current_time = glfwGetTime()/ 1000.0f*1500.0f;
		dt = current_time - last_time;

		//clear color buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		
		//set the camera transformation
		glm::mat4 MV = cam.GetViewMatrix();
		glm::mat4 P = cam.GetProjectionMatrix();
		glm::mat4 MVP = P*MV;

		//render the chekered plane
		checker_plane->Render(glm::value_ptr(MVP));

		//-----------------------------
		//end code 
		//------------------------------
		glfwSwapBuffers(window);
		
	}
	shader.DeleteShaderProgram();
	delete checker_plane;
	glDeleteTextures(1, &checkerTextureID);
	glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (GLFW_PRESS==true) {

		switch (key)
		{
			
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_W:
			cam.Walk(dt);
			break;
		case GLFW_KEY_S:
			cam.Walk(-dt);
			break;
		case GLFW_KEY_A:
			cam.Strafe(-dt);
			break;
		case GLFW_KEY_D:
			cam.Strafe(dt);
			break;
		case GLFW_KEY_Q:
			cam.Lift(dt);
			break;
		case GLFW_KEY_Z:
			cam.Lift(-dt);
			break;
		}
	}
		glm::vec3 t = cam.GetTranslation();
		if (glm::dot(t, t) > EPSILON2) {
			cam.SetTranslation(t*0.95f);
		
	}
}




void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		 mouseX = -xpos*mouse_sensitivity;
		 mouseY = ypos*mouse_sensitivity;
	 //}
	 cam.Rotate(mouseX, mouseY, 0);
 }



void OnInit() {
	GL_CHECK_ERRORS
		//generate the checker texture
		GLubyte data[128][128] = { 0 };
	for (int j = 0; j<128; j++) {
		for (int i = 0; i<128; i++) {
			data[i][j] = (i <= 64 && j <= 64 || i>64 && j>64) ? 255 : 0;
		}
	}
	//generate texture object
	glGenTextures(1, &checkerTextureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, checkerTextureID);
	//set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GL_CHECK_ERRORS

		//set maximum aniostropy setting
		GLfloat largest_supported_anisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropy);

	//set mipmap base and max level
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);

	//allocate texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 128, 128, 0, GL_RED, GL_UNSIGNED_BYTE, data);

	//generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	GL_CHECK_ERRORS

		//create a textured plane object
		checker_plane = new CTexturedPlane();

	GL_CHECK_ERRORS

		//setup camera
		//setup the camera position and look direction
		glm::vec3 p = glm::vec3(5);
	cam.SetPosition(p);
	glm::vec3 look = glm::normalize(p);

	//rotate the camera for proper orientation
	float yaw = glm::degrees(float(atan2(look.z, look.x) + M_PI));
	float pitch = glm::degrees(asin(look.y));
	rX = yaw;
	rY = pitch;
	if (useFiltering) {
		for (int i = 0; i < MOUSE_HISTORY_BUFFER_SIZE; ++i) {
			mouseHistory[i] = glm::vec2(rX, rY);
		}
	}
	cam.Rotate(rX, rY, 0);
	std::cout << "Initialization successfull" << std::endl;
}
