#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Vertex.h"

class Triangle
{
public:
	Triangle(Vertex v1, Vertex v2, Vertex v3);
	virtual ~Triangle();
	void setArea();
	void scale(float scale, float tx, float ty);
	float getArea() const { return area; }
	Vertex getV1() const { return v1; }
	Vertex getV2() const { return v2; }
	Vertex getV3() const { return v3; }

	float xMin;
	float xMax;
	float yMin;
	float yMax;
	Vertex v1;
	Vertex v2;
	Vertex v3;

private:
	float area;
};

#endif
