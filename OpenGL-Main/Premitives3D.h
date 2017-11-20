#pragma once
#include "Premitives2D.h"



class Premitives3D
{
public:
	//variables 
	GLuint vaoID;
	GLuint vboVerticesID;
	GLuint vboIndicesID;
	Premitives3D();
	~Premitives3D();
	void drawReppleMesh(int NUM_X, int NUM_Z);
	void deleteBufferObjs();

private: 
	//------------------------
	// Shader Binders
	//----------------------------
	static GLSLShader bindMeshToShader(const int SIZE_X, const int SIZE_Z);
	//------------------------------------
	// Important matrixes
	//----------------------------
	glm::mat4  P = glm::mat4(1); // projection Mat
	glm::mat4 MV = glm::mat4(1); // Model Mat
	
};

