#pragma once
#include "Node.h"
#include "GeometryFactory.h"

class Cabinet :
	public Node
{
private:
	// Stop the compiler generating methods of copy the object
	Cabinet(Cabinet const& copy);            // Not Implemented
	Cabinet& operator=(Cabinet const& copy); // Not Implemented
public:
	Cabinet(void);
	virtual string getName();
};

