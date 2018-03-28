#pragma once
#include "RenderableObject.h"
#include "FastNoise.h"
class TerrainLoading :
	public RenderableObject
{
public:
	 
	TerrainLoading(const int width = 50, const int depth = 50);
	virtual ~TerrainLoading();
	int GetTotalVertices();
	int GetTotalIndices();
	GLenum GetPrimitiveType();

	void FillVertexBuffer(GLfloat* pBuffer);
	void FillIndexBuffer(GLuint* pBuffer);
	void FillColorBuffer(GLfloat* pBuffer);
	void SetCustomUniforms();
	glm::vec3 getColor(float y);
private:
	int width, depth;
	const int TOTAL = (width*depth);
	int seed = 237;
	float scale = 50;
	glm::vec3 color;
	float half_scale = scale / 2.0f;
	const int HALF_WIDTH = width/2;
	const int HALF_DEPTH = depth/2;
	float AllOFY[];
};

