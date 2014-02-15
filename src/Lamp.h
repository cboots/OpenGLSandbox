#pragma once
#include "Node.h"
#include "GeometryFactory.h"
#include "Utils.h"

class Lamp :
	public Node
{
private:
	// Stop the compiler generating methods of copy the object
	Lamp(Lamp const& copy);            // Not Implemented
	Lamp& operator=(Lamp const& copy); // Not Implemented
public:
	Lamp(void);
	virtual string getName();
};

