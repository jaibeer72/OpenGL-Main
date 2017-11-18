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
