#pragma once
#include "Node.h"
#include "Rendering.h"

class Cylinder :
	public Node
{
private:
	static const int N = 32;
	
	float vertices[(4*N+2)*4];
	float normals[(4*N+2)*4];
	float colors[(4*N+2)*3];
	unsigned short indices[3*N*4];


	// Stop the compiler generating methods of copy the object
	Cylinder(Cylinder const& copy);            // Not Implemented
	Cylinder& operator=(Cylinder const& copy); // Not Implemented
public:
	Cylinder(void);

	
	virtual void draw(mat4, vec3) override;
	virtual string getName() override;
	virtual BoundingBox getBoundingBox() override;
};

