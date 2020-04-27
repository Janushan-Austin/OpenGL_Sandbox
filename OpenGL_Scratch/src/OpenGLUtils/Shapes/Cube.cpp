#include "Cube.h"



Cube::Cube(float width, float height, float depth)
{
	numVertices = 24;
	vertices = new float[numVertices];
}

Cube::Cube(const Cube& copy) {
	CopyCube(copy);
}

const Cube& Cube::CopyCube(const Cube& copy) {

	width = copy.width;
	height = copy.height;
	depth = copy.depth;
	for (int i = 0; i < numVertices; i++) {
		vertices[i] = copy.vertices[i];
	}

	return copy;
}

void Cube::DestroyCube() {
	if (vertices != nullptr) {
		delete[] vertices;
		vertices = nullptr;
	}
	if (indices != nullptr) {
		delete[] indices;
		indices = nullptr;
	}
}

Cube::~Cube()
{
	delete[] vertices;
	delete[] indices;
}
