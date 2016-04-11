#include "Triangle.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3):
	v1(v1),
	v2(v2),
	v3(v3),
	xMin(min(min(v1.getX(), v2.getX()), v3.getX())),
	xMax(max(max(v1.getX(), v2.getX()), v3.getX())),
	yMin(min(min(v1.getY(), v2.getY()), v3.getY())),
	yMax(max(max(v1.getY(), v2.getY()), v3.getY()))
{
}

Triangle::~Triangle()
{
}

void Triangle::scale(float scale, float tx, float ty) {
	v1.setX(scale * v1.getX() + tx);
	v2.setX(scale * v2.getX() + tx);
	v3.setX(scale * v3.getX() + tx);
	v1.setY(scale * v1.getY() + ty);
	v2.setY(scale * v2.getY() + ty);
	v3.setY(scale * v3.getY() + ty);
}

void Triangle::setArea() {
	float x1 = v1.getX();
	float x2 = v2.getX();
	float x3 = v3.getX();

	float y1 = v1.getY();
	float y2 = v2.getY();
	float y3 = v3.getY();

	area = .5 * ((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
}