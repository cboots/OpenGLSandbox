#pragma once
#include "Node.h"
#include "GeometryFactory.h"
#include "Utils.h"
class Table :
	public Node
{
private:
	// Stop the compiler generating methods of copy the object
	Table(Table const& copy);            // Not Implemented
	Table& operator=(Table const& copy); // Not Implemented
public:
	Table(void);
	virtual string getName();
};

