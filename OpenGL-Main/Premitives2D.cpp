#include "Premitives2D.h"

Prem2D::Prem2D()
{
}

Prem2D::~Prem2D()
{
}

void Prem2D::drawPoint(Vertex v1, GLfloat size)
{
	/*glPointSize(size);
	glBegin(GL_POINTS);
	glColor4f(v1.r, v1.g, v1.b, v1.a);
	glVertex3f(v1.x, v1.y, v1.z);
	glEnd();*/
}

void Prem2D::drawLineSegment(Vertex v1, Vertex v2, GLfloat width)
{
	/*glLineWidth(width);
	glBegin(GL_LINES);
	glColor4f(v1.r, v1.g, v1.b, v1.a);
	glVertex3f(v1.x, v1.y, v1.z);
	glColor4f(v2.r, v2.g, v2.b, v2.a);
	glVertex3f(v2.x, v2.y, v2.z);
	glEnd();*/
}

