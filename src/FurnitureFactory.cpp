#include "FurnitureFactory.h"

node_ptr FurnitureFactory::sCabinet = node_ptr();
node_ptr FurnitureFactory::sLamp = node_ptr();
node_ptr FurnitureFactory::sTable = node_ptr();
node_ptr FurnitureFactory::sChair = node_ptr();

node_ptr FurnitureFactory::makeCabinet()
{
	if(sCabinet.get() == NULL)
	{
		sCabinet = node_ptr(new Cabinet());
	}
	//Return shared pointer
	return sCabinet;
}

node_ptr FurnitureFactory::makeLamp()
{
	if(sLamp.get() == NULL)
	{
		sLamp = node_ptr(new Lamp());
	}
	//Return shared pointer
	return sLamp;
}


node_ptr FurnitureFactory::makeChair()
{
	if(sChair.get() == NULL)
	{
		sChair = node_ptr(new Chair());
	}
	//Return shared pointer
	return sChair;
}



node_ptr FurnitureFactory::makeTable()
{
	if(sTable.get() == NULL)
	{
		sTable = node_ptr(new Table());
	}
	//Return shared pointer
	return sTable;
}

