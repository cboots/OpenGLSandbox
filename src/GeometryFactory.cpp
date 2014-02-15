#include "GeometryFactory.h"

//Static initializations to NULL pointers
node_ptr GeometryFactory::sCube = node_ptr();
node_ptr GeometryFactory::sCylinder = node_ptr();
node_ptr GeometryFactory::sSphere = node_ptr();


node_ptr GeometryFactory::makeCube()
{
	if(sCube.get() == NULL)
	{
		sCube = node_ptr(new Cube());
	}
	//Return shared pointer
	return sCube;
}


node_ptr GeometryFactory::makeSphere()
{
	if(sSphere.get() == NULL)
	{
		sSphere = node_ptr(new Sphere());
	}
	//Return shared pointer
	return sSphere;
}


node_ptr GeometryFactory::makeCylinder()
{
	if(sCylinder.get() == NULL)
	{
		sCylinder = node_ptr(new Cylinder());
	}
	//Return shared pointer
	return sCylinder;
}