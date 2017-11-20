#include "Premitives2D.h"

Prem2D::Prem2D()
{
}

Prem2D::~Prem2D()
{
}

void Prem2D::drawPoint(Vertex v1, GLfloat size)
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glColor4f(v1.r, v1.g, v1.b, v1.a);
	glVertex3f(v1.x, v1.y, v1.z);
	glEnd();
}

void Prem2D::drawLineSegment(Vertex v1, Vertex v2, GLfloat width)
{
	glLineWidth(width);
	glBegin(GL_LINES);
	glColor4f(v1.r, v1.g, v1.b, v1.a);
	glVertex3f(v1.x, v1.y, v1.z);
	glColor4f(v2.r, v2.g, v2.b, v2.a);
	glVertex3f(v2.x, v2.y, v2.z);
	glEnd();
}

void Prem2D::drawTriangle(glmVertex v1, glmVertex v2, glmVertex v3)
{
	GLSLShader shader;
	GLushort indices[3];
	shader.LoadFromFile(GL_VERTEX_SHADER, "shader.vert");
	shader.LoadFromFile(GL_FRAGMENT_SHADER, "shader.frag");
	shader.CreateAndLinkProgram();
	shader.Use();
	shader.AddAttribute("vVertex");
	shader.AddAttribute("vColor");
	shader.AddUniform("MVP");
	shader.UnUse();
	glmVertex vertices[3] = { v1,v2,v3 };

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboVerticesID);
	glGenBuffers(1, &vboIndicesID);
	glBindVertexArray(vaoID);
	GLsizei stride = sizeof(glmVertex);
	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(shader["vVertex"]);
	glVertexAttribPointer(shader["vVertex"], 3, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(shader["vColor"]);
	glVertexAttribPointer(shader["vColor"], 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offsetof(glmVertex, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
	
	shader.Use();
	glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	shader.UnUse();
}

void Prem2D::deleteBufferObjs()
{
	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
}
