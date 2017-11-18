#pragma once
#include<GL\glew.h>
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
	GLfloat x, y, z; //position
	GLfloat r, g, b, a; //color and alpha channels
};

class Prem2D
{
public:
	Prem2D();
	~Prem2D();
	void drawPoint(Vertex v1, GLfloat size);

private:

};