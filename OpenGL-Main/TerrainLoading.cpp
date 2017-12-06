#include "TerrainLoading.h"
#include"CFreeCamera.h"
CFreeCamera cam1;
TerrainLoading::TerrainLoading(const int w, const int d,float x, float y)
{
	width = w;
	depth = d;
	xPos = x;
	yPos=y;

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
	
	return (width*depth);
}

int TerrainLoading::GetTotalIndices()
{
	return (width*depth*2*3);
}

GLenum TerrainLoading::GetPrimitiveType()
{
	//glLineWidth(5.0f);
	glPointSize(15.0f);
	return GL_POINTS;
}

void TerrainLoading::FillVertexBuffer(GLfloat * pBuffer)
{
	//PerlinNoise p(230);
	FastNoise NG;
	NG.SetNoiseType(FastNoise::PerlinFractal);
	//NG.SetSeed(500);
	NG.SetFractalOctaves(2);
	NG.SetFrequency(0.01);
	NG.SetFractalLacunarity(10.0);
	float x;
	float z;
	float y;
	glm::vec3* vertices = (glm::vec3*)(pBuffer);
	//setup vertices 
	int count = 0;

	//fill terrain vertices
	//glm::vec3 trans = cam1.GetPosition();
	for (int j = 0; j<depth; j++) {
		for (int i = 0; i<width; i++) {
			x = ((float(i)-(width/2) / (width/2 - 1)*(width/2)));
			z = ((float(j)-(depth/2) / (depth/2 - 1)*(depth/2)));
			
			y =20*NG.GetNoise(x, z);
			
			vertices[count] = glm::vec3(x,y,z);
			count++;
			if (i == 0 && j == 0) {
				SetMin(glm::vec2(vertices[count].x, vertices[count].z));
			}
			//std::cout << "Y CORD OF PLAIN :- " << y << "\n";
		}
	}
	SetMax(glm::vec2(vertices[count].x, vertices[count].z));
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

void TerrainLoading::SetCustomUniforms()
{

}

void TerrainLoading::SetMax(const glm::vec2 trans)
{
	max = trans;
}

glm::vec2 TerrainLoading::Getmax()
{
	return max;
}

void TerrainLoading::SetMin(glm::vec2 trans)
{
	min = trans;
}

glm::vec2 TerrainLoading::GetMin()
{
	return min;
}

glm::vec2 TerrainLoading::getCamPos(glm::vec2 camPos)
{
	return glm::vec2(camPos);
}

