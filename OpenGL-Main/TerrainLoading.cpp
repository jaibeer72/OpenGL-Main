#include "TerrainLoading.h"

TerrainLoading::TerrainLoading(const int w, const int d)
{
	width = w;
	depth = d;

	shader.LoadFromFile(GL_VERTEX_SHADER, "Tarrain.vert");
	shader.LoadFromFile(GL_FRAGMENT_SHADER, "Tarrain.frag");
	std::cout << "Load Sucessful";
	shader.CreateAndLinkProgram();
	std::cout << "Link sucessful";
	shader.Use();
	//add attributes and uniforms
	shader.AddAttribute("vVertex");
	shader.AddUniform("heightMapTexture");
	shader.AddUniform("scale");
	shader.AddUniform("half_scale");
	shader.AddUniform("HALF_TERRAIN_SIZE");
	shader.AddUniform("MVP");
	shader.AddUniform("vColor");
	//glUniform3fv(shader("vColor"), 1, color);
	//set values of constant uniforms as initialization	
	glUniform1i(shader("heightMapTexture"), 0);
	glUniform2i(shader("HALF_TERRAIN_SIZE"),w>>1,d>>1);
	glUniform1f(shader("scale"), scale);
	glUniform1f(shader("half_scale"), half_scale);
	shader.UnUse();
	std::cout << "SucessfulBind"; 
	Init();
}

TerrainLoading::~TerrainLoading()
{
}

int TerrainLoading::GetTotalVertices()
{
	
	return (2*(width*depth));
}

int TerrainLoading::GetTotalIndices()
{
	return (2*(width*depth*2*3));
}

GLenum TerrainLoading::GetPrimitiveType()
{
	return GL_TRIANGLES;
}

void TerrainLoading::FillVertexBuffer(GLfloat * pBuffer)
{
	//PerlinNoise p(230);
	FastNoise NG;
	NG.SetNoiseType(FastNoise::Perlin);
	NG.SetSeed(500);
	NG.SetFractalOctaves(10);
	NG.SetFrequency(0.5);
	NG.SetFractalLacunarity(5.0);

	glm::vec3* vertices = (glm::vec3*)(pBuffer);
	//setup vertices 
	int count = 0;
	//fill terrain vertices
	for (int j = 0; j<depth; j++) {
		for (int i = 0; i<width; i++) {
			float x = ((float(i)) / (width - 1))*(width/2);
			float z = (float(j)) / (depth - 1)*(depth/2);
			float y = 2*NG.GetNoise(x, z);
			AllOFY[count] = y; 
			vertices[count] = glm::vec3(x,y,z);
			count++;
			//color = getColor(y);
		}
	}
}

void TerrainLoading::FillIndexBuffer(GLuint * pBuffer)
{
	GLuint* id = pBuffer;
	for (int i = 0; i < depth - 1; i++) {
		for (int j = 0; j < width - 1; j++) {
			int i0 = j + i*width;
			int i1 = i0 + 1;
			int i2 = i0 + width;
			int i3 = i2 + 1;
			
			*id++ = i0;
			*id++ = i2;
			*id++ = i1;
			*id++ = i1;
			*id++ = i2;
			*id++ = i3;
		}
	}
}

void TerrainLoading::FillColorBuffer(GLfloat * pBuffer)
{
	glm::vec3* color = (glm::vec3*)(pBuffer);
	int i = 0;
	while (i>depth*width)
	{
		if (AllOFY[i]<0 && AllOFY[i]>0.5) {
			color[i] = glm::vec3(0.5, 0.3, 0.3);
		}
		else
		{
			color[i] = glm::vec3(1.0, 1.0, 1.0);
		}
	}
}

void TerrainLoading::SetCustomUniforms()
{
	glUniform3fv(shader("vColor"), 1, glm::value_ptr(color));
}

glm::vec3 TerrainLoading::getColor(float y)
{
	if (y > 0 && y < 0.5) {
		return glm::vec3(1.0,0.5,0.6);
	}
	else
	{
		return glm::vec3(1.0, 1.0, 1.0);
	}
	
}

