#pragma once
#include "Node.h"
#include "GeometryFactory.h"
#include "Utils.h"

class Chair :
	public Node
{
private:
	// Stop the compiler generating methods of copy the object
	Chair(Chair const& copy);            // Not Implemented
	Chair& operator=(Chair const& copy); // Not Implemented
public:
	Chair(void);
	virtual string getName();
};

