#pragma once
#include "Node.h"
#include "GeometryFactory.h"
#include "Utils.h"

#define FLOOR_THICKNESS 0.05f

class Floor :
	public Node
{
public:
	Floor(int xSize, int zSize);
	~Floor(void);
	virtual string getName();
};

