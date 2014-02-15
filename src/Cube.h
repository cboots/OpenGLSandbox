#pragma once
#include "Node.h"
#include "Rendering.h"

class Cube :
	public Node
{
private:
	float vertices[8*4*3];
	float normals[8*4*3];
	float colors[8*3*3];
	unsigned short indices[3*2*6];

	
	// Stop the compiler generating methods of copy the object
	Cube(Cube const& copy);            // Not Implemented
	Cube& operator=(Cube const& copy); // Not Implemented
public:
	Cube(void);
	
	virtual void draw(mat4, vec3) override;
	virtual string getName() override;
	virtual BoundingBox getBoundingBox() override;
};

