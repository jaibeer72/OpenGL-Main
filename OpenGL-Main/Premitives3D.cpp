#include "Premitives3D.h"
#include"Premitives2D.h"

float rX = 25, rY = -40, dist = -35;

Premitives3D::Premitives3D()
{
}


Premitives3D::~Premitives3D()
{	
	GLSLShader shader;
	shader.DeleteShaderProgram();
	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
	glDeleteVertexArrays(1, &vaoID);
}

void Premitives3D::drawReppleMesh(const int SIZE_X,const int SIZE_Z)
{

	const float SPEED = 500.0f;
	float time = 0;
	const int NUM_X = 40; 
	const int NUM_Z = 40; 
	static GLSLShader shader=bindMeshToShader(SIZE_X,SIZE_Z);
	glm::vec3 vertices[(NUM_X + 1)*(NUM_Z + 1)];
	const int TOTAL_INDICES = NUM_X*NUM_Z * 2 * 3;
	GLushort indices[TOTAL_INDICES];
	float rX = 25, rY = -40, dist = -7;
	//const float SIZE_X = 4; //size of plane in world space
	//const float SIZE_Z = 4;
	const float HALF_SIZE_X = SIZE_X / 2.0f;
	const float HALF_SIZE_Z = SIZE_Z / 2.0f;
	
	
	P = glm::perspective(45.0f, (GLfloat)640 / 480, 1.f, 1000.f);
	time = glfwGetTime() / 1000.0f * SPEED;
	glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, dist));
	glm::mat4 Rx = glm::rotate(T, rX, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 MV = glm::rotate(Rx, rY, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 MVP = P*MV;
	shader.Use();
	glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
	glUniform1f(shader("time"), time);
	glDrawElements(GL_TRIANGLES, TOTAL_INDICES, GL_UNSIGNED_SHORT, 0);
	shader.UnUse();
}
void Premitives3D::deleteBufferObjs()
{
	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
}

void Premitives3D::drawPlain(glm::vec3 vertices[],int sub_divisions)
{
	bindPlainToShader(vertices, sub_divisions);
	GLSLShader shader;
	glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, dist));
	glm::mat4 Rx = glm::rotate(T, rX, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 MV = glm::rotate(Rx, rY, glm::vec3(0.0f, 1.0f, 0.0f));
	MV = glm::translate(MV, glm::vec3(-5, 0, -5));
	shader.Use();
	glUniform1i(shader("sub_divisions"), sub_divisions);
	glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	MV = glm::translate(MV, glm::vec3(10, 0, 0));
	glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	MV = glm::translate(MV, glm::vec3(0, 0, 10));
	glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	MV = glm::translate(MV, glm::vec3(-10, 0, 0));
	glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	shader.UnUse();
}

GLSLShader Premitives3D::bindMeshToShader(const int SIZE_X, const int SIZE_Z)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	const float SPEED = 2;
	float time = 0;
	const int NUM_X = 40;
	const int NUM_Z = 40;
	glm::vec3 vertices[(NUM_X + 1)*(NUM_Z + 1)];
	const int TOTAL_INDICES = NUM_X*NUM_Z * 2 * 3;
	GLushort indices[TOTAL_INDICES];
	float rX = 25, rY = -40, dist = -7;
//	const float SIZE_X = 4; //size of plane in world space
	//const float SIZE_Z = 4;
	const float HALF_SIZE_X = SIZE_X / 2.0f;
	const float HALF_SIZE_Z = SIZE_Z / 2.0f;

	GLSLShader shader;
	shader.LoadFromFile(GL_VERTEX_SHADER, "rippleMesh.vert");
	shader.LoadFromFile(GL_FRAGMENT_SHADER, "rippleMesh.frag");
	shader.CreateAndLinkProgram();
	shader.Use();
	shader.AddAttribute("vVertex");
	shader.AddAttribute("vColor");
	shader.AddUniform("MVP");
	shader.UnUse();
	//glmVertex vertices[NUM_X][NUM_Z];
	int count = 0;
	int i = 0, j = 0;
	for (j = 0; j <= NUM_Z; j++) {
		for (i = 0; i <= NUM_X; i++) {
			vertices[count++] = glm::vec3(((float(i) / (NUM_X - 1)) * 2 - 1)* HALF_SIZE_X, 0, ((float(j) / (NUM_Z - 1)) * 2 - 1)*HALF_SIZE_Z);
		}
	}
	GLushort* id = &indices[0];
	for (i = 0; i < NUM_Z; i++) {
		for (j = 0; j < NUM_X; j++) {
			int i0 = i * (NUM_X + 1) + j;
			int i1 = i0 + 1;
			int i2 = i0 + (NUM_X + 1);
			int i3 = i2 + 1;
			if ((j + i) % 2) {
				*id++ = i0; *id++ = i2; *id++ = i1;
				*id++ = i1; *id++ = i2; *id++ = i3;
			}
			else {
				*id++ = i0; *id++ = i2; *id++ = i3;
				*id++ = i0; *id++ = i3; *id++ = i1;
			}
		}
	}
	GLuint vaoID;
	GLuint vboVerticesID;
	GLuint vboIndicesID;
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboVerticesID);
	glGenBuffers(1, &vboIndicesID);
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(shader["vVertex"]);
	glVertexAttribPointer(shader["vVertex"], 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
	return shader;
}

void Premitives3D::bindPlainToShader(glm::vec3 vertices[],int sub_divisions)
{
	GLuint vaoID;
	GLuint vboVerticesID;
	GLuint vboIndicesID;
	GLSLShader shader;
	GLushort indices[6];
	shader.LoadFromFile(GL_VERTEX_SHADER, "shader.vert");
	shader.LoadFromFile(GL_GEOMETRY_SHADER, "shader.geom");
	shader.LoadFromFile(GL_FRAGMENT_SHADER, "shader.frag");
	shader.CreateAndLinkProgram();
	shader.Use();
	shader.AddAttribute("vVertex");
	shader.AddUniform("MVP");
	shader.AddUniform("sub_divisions");
	glUniform1i(shader("sub_divisions"), sub_divisions);
	shader.UnUse();
	vertices[0] = glm::vec3(-5, 0, -5);
	vertices[1] = glm::vec3(-5, 0, 5);
	vertices[2] = glm::vec3(5, 0, 5);
	vertices[3] = glm::vec3(5, 0, -5);
	GLushort* id = &indices[0];

	*id++ = 0;
	*id++ = 1;
	*id++ = 2;
	*id++ = 0;
	*id++ = 2;
	*id++ = 3;

	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboVerticesID);
	glGenBuffers(1, &vboIndicesID);
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(shader["vVertex"]);
	glVertexAttribPointer(shader["vVertex"], 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
