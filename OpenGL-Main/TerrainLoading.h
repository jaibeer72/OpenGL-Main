#pragma once
#include "RenderableObject.h"
#include "FastNoise.h"
class TerrainLoading :
	public RenderableObject
{
public:
	 
	TerrainLoading(const int width = 512, const int depth = 512);
	virtual ~TerrainLoading();
	int GetTotalVertices();
	int GetTotalIndices();
	GLenum GetPrimitiveType();

	void FillVertexBuffer(GLfloat* pBuffer);
	void FillIndexBuffer(GLuint* pBuffer);
	void SetCustomUniforms();
private:
	int width, depth;
	const int TOTAL = (width*depth);
	int seed = 237;
	float scale = 50;
	float half_scale = scale / 2.0f;
	const int HALF_WIDTH = width/2;
	const int HALF_DEPTH = depth/2;
};

