#pragma once
#include<GL\glew.h>
#include"GLSLShader.h"
#include <GLFW\glfw3.h>

#include<string>
#include<map>
#include<vector>
//GLM
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtc\type_ptr.hpp>

typedef struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
};

//typedef struct Vertex
//{
//	GLfloat x, y, z; //position
//	GLfloat r, g, b, a; //color and alpha channels
//};
typedef struct Data {
	GLfloat x, y, z; 
};

class Prem2D
{
public:
	Prem2D();
	~Prem2D();
	void drawPoint(Vertex v1, GLfloat size);
	void drawLineSegment(Vertex v1, Vertex v2, GLfloat width); 

private:

};