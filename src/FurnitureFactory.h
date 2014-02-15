#pragma once
#include "Node.h"
#include "Cabinet.h"
#include "Chair.h"
#include "Table.h"
#include "Lamp.h"

class FurnitureFactory
{
	FurnitureFactory(void);
	~FurnitureFactory(void);
	static node_ptr sCabinet;
	static node_ptr sLamp;
	static node_ptr sTable;
	static node_ptr sChair;
public:
	static node_ptr makeCabinet();
	static node_ptr makeLamp();
	static node_ptr makeTable();
	static node_ptr makeChair();
};

