#pragma once
#ifndef _VERTEX_H_
#define _VERTEX_H_

class Vertex
{
public:
	Vertex(float x, float y, float z, int r, int g, int b);
	virtual ~Vertex();
	//void drawVertex(void *ptr);
	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
	void setX(float xIn);
	void setY(float yIn);
	void setZ(float zIn);
	int getR() const { return r; }
	int getG() const { return g; }
	int getB() const { return b; }

private:
	float x;
	float y;
	float z;
	int r;
	int g;
	int b;
};

#endif
