
// Headers and the objs 
#include"OpenGL-Main.h"
#include"GLSLShader.h"
//#include"Premitives3D.h"
#include"CFreeCamera.h"
#include"CTexturedPlane.h"
#include"TerrainLoading.h"
#include"CSkybox.h"

#define _USE_MATH_DEFINES // M_PI constant
#include<math.h>// This has to be declared after the define function NO CLUE WHy . 
//objs

#define GL_CHECK_ERRORS assert(glGetError()== GL_NO_ERROR);

OpenGLsetup OGL;
GLSLShader shader;
CSkybox* skybox;
//Premitives3D prem3D;
CFreeCamera cam; 
TerrainLoading* Terrain;
//When using multyple of the same kind of class :P 
//YAY pointers finally 

CTexturedPlane* checker_plane;

bool created = false; 
bool isRendered = false; 
GLuint skyboxTextureID;
//===============================
// Function Declaration
//---------------------------=------

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
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
const int Window_Width=1920;
const int Window_Height=1080;
const float MOUSE_FILTER_WEIGHT = 0.75f;
const int MOUSE_HISTORY_BUFFER_SIZE = 10;// ill figure this later
glm::vec2 mouseHistory[MOUSE_HISTORY_BUFFER_SIZE];
float mouseX = 0, mouseY = 0;
const int T_width =512;
const int T_depth =512;
//flag to enable filtering
bool useFiltering = true;
const char* texture_names[6] = { "skybox/posx.png",
"skybox/negx.png", 
"skybox/posy.png", 
"skybox/negy.png", 
"skybox/posz.png", 
"skybox/negz.png", };
//mouse click handler
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
//bool created = false;
//timing related variables
float last_time = 0, current_time = 0;



// Texture Variable 


///------------------------------------------
//------------------------------------
// Important matrixes
//----------------------------

glm::mat4  P = glm::mat4(1); // projection Mat
glm::mat4 MV = glm::mat4(1); // Model Mat

void renderManager(glm::mat4 MVP);
void main() {
	GLFWwindow* window = OGL.CreateWindow(Window_Width, Window_Height, "This Is a Window Name");
  //GLFWwindow* window = OGL.CreateWindow(Window_Width, Window_Height, "This Is a Window Name");
	
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(5.0f);
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
		glm::mat4 S = glm::scale(glm::mat4(1), glm::vec3(1000.0));
		glm::mat4 MVPS = P*MV*S;
		renderManager(MVP);
		skybox->Render(glm::value_ptr(MVPS));
		//render the chekered plane
		//checker_plane->Render(glm::value_ptr(MVP));
		
		
		//-----------------------------
		//end code 
		//------------------------------
		glfwSwapBuffers(window);
		
	}
	shader.DeleteShaderProgram();;
	glDeleteTextures(1, &skyboxTextureID);
	glfwDestroyWindow(window);
  glfwTerminate();
 
  exit(EXIT_SUCCESS);
}
float x = 3, y = 3;
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
		glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	GL_CHECK_ERRORS

		//generate a new Skybox
		skybox = new CSkybox();

	GL_CHECK_ERRORS

		//load skybox textures using SOIL
		int texture_widths[6];
	int texture_heights[6];
	int channels[6];
	GLubyte* pData[6];

	std::cout << "Loading skybox images: ..." << std::endl;
	for (int i = 0; i<6; i++) {
		std::cout << "\tLoading: " << texture_names[i] << " ... ";
		pData[i] = SOIL_load_image(texture_names[i], &texture_widths[i], &texture_heights[i], &channels[i], SOIL_LOAD_AUTO);
		std::cout << "done." << std::endl;
	}

	GL_CHECK_ERRORS

		//generate OpenGL texture
		glGenTextures(1, &skyboxTextureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);

	GL_CHECK_ERRORS
		//set texture parameters
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	GL_CHECK_ERRORS
		
		//set the image format
		GLint format = (channels[0] == 4) ? GL_RGBA : GL_RGB;
	//load the 6 images
	for (int i = 0; i<6; i++) {
		//allocate cubemap data
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, texture_widths[i], texture_heights[i], 0, format, GL_UNSIGNED_BYTE, pData[i]);

		//free SOIL image data
		SOIL_free_image_data(pData[i]);
	}


		//setup camera
		//setup the camera position and look direction
		glm::vec3 p = glm::vec3(10.0,10.0,0.0);
	cam.SetPosition(p);
	glm::vec3 look = glm::normalize(p);
	//glm::vec3 trans = cam.GetPosition();
	//Terrain = new TerrainLoading(T_width, T_depth, trans.x, trans.z);
	
	//rotate the camera for proper orientation
	//float yaw = glm::degrees(float(atan2(look.z, look.x) + M_PI));
	//float pitch = glm::degrees(asin(look.y));
	//rX = yaw;
	//rY = pitch;
	//if (useFiltering) {
	//	for (int i = 0; i < MOUSE_HISTORY_BUFFER_SIZE; ++i) {
	//		mouseHistory[i] = glm::vec2(rX, rY);
	//	}
	//}
	//cam.Rotate(rX, rY, 0);
	std::cout << "Initialization successfull" << std::endl;
}

void renderManager(glm::mat4 MVP)
{
	glm::vec3 trans = cam.GetPosition();
	if (created==false){
		
		Terrain = new TerrainLoading(T_width, T_depth, trans.x, trans.z);
		created = true;
	}
	if(created==true) {
		glm::vec2 max, min;
		max = Terrain->Getmax();
		min = Terrain->GetMin();
		Terrain->Render(glm::value_ptr(MVP));
		/*if (trans.x > max.x || trans.x < min.x || trans.z<min.y || trans.z>max.y) {
			TerrainLoading* T2 = new TerrainLoading(T_width, T_depth, trans.x, trans.z);
			Terrain->Destroy(); 
			Terrain =T2 ;
			delete[] T2; 
			created = false;
		}*/
	}
}

	
