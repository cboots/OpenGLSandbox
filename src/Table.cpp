#include "Table.h"


Table::Table(void)
{
	cout<<"Initializing a Table Object. Should only happen Once"<<endl;
	node_ptr root = node_ptr(new Node(translate(scale( mat4(1.0f),vec3(1,1,1)), vec3(0,0.5,0))));
	addChild(root);
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3(-0.4, -0.1, -0.4)), vec3(0.1,0.8,0.1)), vec3(0.4,0.2,0), GeometryFactory::makeCylinder())));
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3( 0.4, -0.1, -0.4)), vec3(0.1,0.8,0.1)), vec3(0.4,0.2,0), GeometryFactory::makeCylinder())));
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3(-0.4, -0.1,  0.4)), vec3(0.1,0.8,0.1)), vec3(0.4,0.2,0), GeometryFactory::makeCylinder())));
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3( 0.4, -0.1,  0.4)), vec3(0.1,0.8,0.1)), vec3(0.4,0.2,0), GeometryFactory::makeCylinder())));
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3( 0, 0.4, 0)), vec3(1, 0.1, 1)), vec3(-1,-1,-1), GeometryFactory::makeCube())));
}



string Table::getName()
{
	return "Table";
}