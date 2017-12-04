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

typedef struct glmVertex
{
	glm::vec3 position;
	glm::vec4 color;
};


typedef struct Vertex
{
	GLfloat x, y, z; //position
	GLfloat r, g, b, a; //color and alpha channels
};
typedef struct Data {
	GLfloat x, y, z; 
};

class Prem2D
{
public:
	//variables 
	
	GLuint vaoID;
	GLuint vboVerticesID;
	GLuint vboIndicesID;
	//functions
	Prem2D();
	~Prem2D();
	void drawPoint(Vertex v1, GLfloat size);
	void drawLineSegment(Vertex v1, Vertex v2, GLfloat width); 
	void drawTriangle(glmVertex v1, glmVertex v2, glmVertex v3);
	void deleteBufferObjs();
private:
	//------------------------------------
	// Important matrixes
	//----------------------------

	glm::mat4  P = glm::mat4(1); // projection Mat
	glm::mat4 MV = glm::mat4(1); // Model Mat
};