#include "Vertex.h"
#include "Image.h"
#include <stdio.h>


Vertex::Vertex(float x, float y, float z, int r, int g, int b) :
	x(x),
	y(y),
	z(z),
	r(r),
	g(g),
	b(b)
	{
	}

Vertex::~Vertex()
{
}

void Vertex::setX(float xIn) {
	x = xIn;
}

void Vertex::setY(float yIn) {
	y = yIn;
}

void Vertex::setZ(float zIn) {
	z = zIn;
}

// void Vertex::drawVertex(Image &image) {
// 	//printf("x: %d y: %d\n", x, y);
// 	//((Image *) ptr)->setPixel(x, y, r, g, b);
// }