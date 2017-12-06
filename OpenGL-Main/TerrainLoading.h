#pragma once
#include "RenderableObject.h"
#include "FastNoise.h"
class TerrainLoading :
	public RenderableObject
{
public:
	 
	TerrainLoading(const int width = 512, const int depth = 512,float xPos=0,float yPos=0);
	virtual ~TerrainLoading();
	int GetTotalVertices();
	int GetTotalIndices();
	GLenum GetPrimitiveType();

	void FillVertexBuffer(GLfloat* pBuffer);
	void FillIndexBuffer(GLuint* pBuffer);
	void SetCustomUniforms();
	void SetMax(const glm::vec2 trans);
	glm::vec2 Getmax();
	void SetMin(const glm::vec2 trans);
	glm::vec2 GetMin();
	glm::vec2 getCamPos(glm::vec2 camPos);

private:
	int width, depth;
	float xPos, yPos; 
	float x;
	float z;
	float y;
	const int TOTAL = (width*depth);
	int seed = 237;
	float scale = 50;
	glm::vec2 max;
	glm::vec2 min;
	float half_scale = scale / 2.0f;
	const int HALF_WIDTH = width/2;
	const int HALF_DEPTH = depth/2;
};

