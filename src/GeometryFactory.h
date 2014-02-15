#pragma once
#include "Node.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"

class GeometryFactory
{
private:
	static node_ptr sCube;
	static node_ptr sCylinder;
	static node_ptr sSphere;

	GeometryFactory(void);
	~GeometryFactory(void);

public:

	static node_ptr makeCube();
	static node_ptr makeCylinder();
	static node_ptr makeSphere();
};

