#include "Floor.h"


Floor::Floor(int xSize, int zSize) 
{

	float floorThickness = 0.1f;
	//We want to perform translation in world space so do that before scaling.
	mTransform = glm::translate(mTransform, vec3((xSize-1)/2.0, -floorThickness/2, (zSize-1)/2.0));
	mTransform = glm::scale(mTransform, vec3(xSize, floorThickness, zSize));
	mColor = glm::vec3(0.5, 0.5, 0.5);//TODO: Set good color

	mGeometry = GeometryFactory::makeCube();
}


Floor::~Floor(void)
{

}


string Floor::getName()
{
	return "Floor";
}
