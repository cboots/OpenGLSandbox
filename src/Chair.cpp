#include "Chair.h"


Chair::Chair(void)
{
	cout<<"Initializing a Chair Object. Should only happen Once"<<endl;
	node_ptr root = node_ptr(new Node(translate(scale( mat4(1.0f),vec3(1,1,1)), vec3(0,0.5,0))));
	addChild(root);
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3(-0.2, -0.3, -0.2)), vec3(0.1,0.4,0.1)), vec3(0.75,0.75,0.75), GeometryFactory::makeCylinder())));
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3( 0.2, -0.3, -0.2)), vec3(0.1,0.4,0.1)), vec3(0.75,0.75,0.75), GeometryFactory::makeCylinder())));
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3(-0.2, -0.3,  0.2)), vec3(0.1,0.4,0.1)), vec3(0.75,0.75,0.75), GeometryFactory::makeCylinder())));
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3( 0.2, -0.3,  0.2)), vec3(0.1,0.4,0.1)), vec3(0.75,0.75,0.75), GeometryFactory::makeCylinder())));
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3( 0, -0.05, 0)), vec3(0.5, 0.1, 0.5)), vec3(-1,-1,-1), GeometryFactory::makeCube())));
	root->addChild(node_ptr(new Node(scale(translate(mat4(1.0f),vec3( 0.20,  0.25, 0)), vec3(0.1, 0.5, 0.5)), vec3(-1,-1,-1), GeometryFactory::makeCube())));
}


string Chair::getName()
{
	return "Chair";
}