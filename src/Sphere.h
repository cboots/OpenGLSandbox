#pragma once
#include "Node.h"
#include "Rendering.h"


class Sphere :
	public Node
{
private:
	int rings;
	int sectors;

	vector<float> vertices;
	vector<float> normals;
	vector<float> colors;
	vector<unsigned short> indices;

	// Stop the compiler generating methods of copy the object
	Sphere(Sphere const& copy);            // Not Implemented
	Sphere& operator=(Sphere const& copy); // Not Implemented
public:
	Sphere(void);

	
	virtual void draw(mat4, vec3) override;
	virtual string getName() override;
	virtual BoundingBox getBoundingBox() override;
};

