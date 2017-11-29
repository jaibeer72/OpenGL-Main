
// Headers and the objs 
#include"Premitives2D.h"
#include"OpenGL-Main.h"
#include"GLSLShader.h"


#define _USE_MATH_DEFINES // M_PI constant
#include<math.h>// This has to be declared after the define function NO CLUE WHy . 
//objs



OpenGLsetup OGL;
Prem2D prem2D; 
GLSLShader shader;
//===============================
// Demo Text Functions from the book 
//---------------------------=------


///---------------------------------------------------------
//-------------------------------
//Global Variables
//---------------------------
const int Window_Width=640*2;
const int Window_Height=480;
glmVertex vertices[3];
GLushort indices[3];
GLuint vaoID;
GLuint vboVerticesID;
GLuint vboIndicesID;

///------------------------------------------

//------------------------------------
// Important matrixes
//----------------------------

glm::mat4  P = glm::mat4(1); // projection Mat
glm::mat4 MV = glm::mat4(1); // Model Mat

void main() {
	GLFWwindow* window = OGL.CreateWindow(Window_Width, Window_Height, "This Is a Window Name");
  //GLFWwindow* window = OGL.CreateWindow(Window_Width, Window_Height, "This Is a Window Name");
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
	shader.LoadFromFile(GL_VERTEX_SHADER, "shader.vert");
	shader.LoadFromFile(GL_FRAGMENT_SHADER, "shader.frag");
	shader.CreateAndLinkProgram();
	shader.Use();
	shader.AddAttribute("vVertex");
	shader.AddAttribute("vColor");
	shader.AddUniform("MVP");
	shader.UnUse();

	//Triangle Coord
	vertices[0].color = glm::vec3(1, 0, 0);
	vertices[1].color = glm::vec3(0, 1, 0);
	vertices[2].color = glm::vec3(0, 0, 1);

	vertices[0].position = glm::vec3(-1, -1, 0);
	vertices[1].position = glm::vec3(0, 1, 0);
	vertices[2].position = glm::vec3(1, -1, 0);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboVerticesID);
	glGenBuffers(1, &vboIndicesID);
	glBindVertexArray(vaoID);
	GLsizei stride = sizeof(glmVertex);
	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(shader["vVertex"]);
	glVertexAttribPointer(shader["vVertex"], 3, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(shader["vColor"]);
	glVertexAttribPointer(shader["vColor"], 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offsetof(glmVertex, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
	
	while (!glfwWindowShouldClose(window))
	{
		OGL.Ortho_Projection_Setup(window, Window_Width, Window_Height);
		//OGL.PrespectiveCamera_Setup(window, Window_Width, Window_Height); 
		
		//--------------------------
		// enter code here 
		//------------------------
		
		shader.Use();
		glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
		shader.UnUse();
	
		//-----------------------------
		//end code 
		//------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	shader.DeleteShaderProgram();
	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
	glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}


