#include "Lamp.h"


Lamp::Lamp(void)
{
	//TODO: Build Lamp subgraph
	cout<<"Initializing a Lamp Object. Should only happen Once"<<endl;
	node_ptr root = node_ptr(new Node(translate(scale( mat4(1.0f),vec3(1,1,1)), vec3(0,0.5,0))));
	addChild(root);
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3( 0, -0.3, 0)),  vec3(0.2, 0.4, 0.2)), vec3(-1,-1,-1), GeometryFactory::makeCylinder())));
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3( 0, -0.375, 0)), vec3(0.4, 0.25, 0.4)), vec3(-1,-1,-1), GeometryFactory::makeSphere())));
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3( 0, -0.1, 0)),  vec3(0.5, 0.25, 0.5)), vec3(1,1,0.8), GeometryFactory::makeCylinder())));
}




string Lamp::getName()
{
	return "Lamp";
}