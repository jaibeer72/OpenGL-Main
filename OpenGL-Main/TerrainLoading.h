#pragma once
#include "RenderableObject.h"
#include "FastNoise.h"
class TerrainLoading :
	public RenderableObject
{
public:
	 
<<<<<<< HEAD
	TerrainLoading(const int width = 512, const int depth = 512,float xPos=0,float yPos=0);
=======
	TerrainLoading(const int width = 50, const int depth = 50);
>>>>>>> 22e312b4fe88051521d0e646757de75c1643c424
	virtual ~TerrainLoading();
	int GetTotalVertices();
	int GetTotalIndices();
	GLenum GetPrimitiveType();

	void FillVertexBuffer(GLfloat* pBuffer);
	void FillIndexBuffer(GLuint* pBuffer);
	void FillColorBuffer(GLfloat* pBuffer);
	void SetCustomUniforms();
<<<<<<< HEAD
	void SetMax(const glm::vec2 trans);
	glm::vec2 Getmax();
	void SetMin(const glm::vec2 trans);
	glm::vec2 GetMin();
	glm::vec2 getCamPos(glm::vec2 camPos);

=======
	glm::vec3 getColor(float y);
>>>>>>> 22e312b4fe88051521d0e646757de75c1643c424
private:
	int width, depth;
	float xPos, yPos; 
	float x;
	float z;
	float y;
	const int TOTAL = (width*depth);
	int seed = 237;
	float scale = 50;
<<<<<<< HEAD
	glm::vec2 max;
	glm::vec2 min;
=======
	glm::vec3 color;
>>>>>>> 22e312b4fe88051521d0e646757de75c1643c424
	float half_scale = scale / 2.0f;
	const int HALF_WIDTH = width/2;
	const int HALF_DEPTH = depth/2;
	float AllOFY[];
};

