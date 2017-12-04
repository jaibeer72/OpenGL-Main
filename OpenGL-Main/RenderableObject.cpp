#include "RenderableObject.h"

typedef struct Vertex {
	GLfloat* pBuffer;
	GLfloat* pCBuffer;
};


RenderableObject::RenderableObject(void)
{

}


RenderableObject::~RenderableObject(void)
{
	Destroy();
}

void RenderableObject::Render(const float * MVP)
{
	shader.Use();
	glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, MVP);
	SetCustomUniforms();
	glBindVertexArray(vaoID);
	glDrawElements(primType, totalIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	shader.UnUse();
}

void RenderableObject::Init() {
	Vertex v;
	//setup vao and vbo stuff
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboVerticesID);
	glGenBuffers(1, &vboIndicesID);

	//get total vertices and indices
	totalVertices = GetTotalVertices();
	totalIndices = GetTotalIndices();
	primType = GetPrimitiveType();

	//now allocate buffers
	glBindVertexArray(vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, totalVertices * sizeof(glm::vec3*), 0, GL_STATIC_DRAW);

	v.pBuffer = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	FillVertexBuffer(v.pBuffer);
	v.pCBuffer = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	FillColorBuffer(v.pCBuffer);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glEnableVertexAttribArray(shader["vVertex"]);
	glVertexAttribPointer(shader["vVertex"], 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(shader["vColor"]);
	glVertexAttribPointer(shader["vColor"], 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, pCBuffer));


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalIndices * sizeof(GLuint), 0, GL_STATIC_DRAW);

	GLuint* pIBuffer = static_cast<GLuint*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
	FillIndexBuffer(pIBuffer);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	glBindVertexArray(0);
}

void RenderableObject::Destroy() {
	//Destroy shader
	shader.DeleteShaderProgram();

	//Destroy vao and vbo
	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
	glDeleteVertexArrays(1, &vaoID);
}

