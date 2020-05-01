#pragma once
class Cube
{
public:
	Cube(float = 1.0f, float = 1.0f, float = 1.0f);
	Cube(const Cube&);
	~Cube();

	const Cube& CopyCube(const Cube&);

private:
	void DestroyCube();

	float width, height, depth;
	float * vertices;
	float * indices;
	int numVertices;
};

