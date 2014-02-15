#pragma once
#include "Utils.h"
#include <stack>
#include "Node.h"
#include "FurnitureFactory.h"
#include "Floor.h"

struct TraversalState{
	node_ptr node;
	mat4 contextView;
	TraversalState(node_ptr n, mat4 ctx)
	{
		contextView = ctx;
		node = n;
	}
};

class SceneGraph
{
private:
    ifstream fp_in;
	node_ptr root;
	int xSize;
	int zSize;
	int numItems;

	//Traversal status
	stack<TraversalState> mTraversalStack;

	void addFurniture(string line);
	bool findFirstCollisionXY(node_ptr parent, node_ptr& c1_out, node_ptr& c2_out);
	void insertNode(node_ptr parent, node_ptr newNode);
	void resolveCollisions(node_ptr parent);
	void stackFurniture(node_ptr parent, node_ptr newNode);
	void deleteNode(node_ptr node);
public:
	SceneGraph(string filename);
	~SceneGraph(void);
	void draw(void);
	void printGraph(void);
	void resetTraversal(void);
	void stepTraversal(void);
	
	void rotateSelection(float deg);
	void incrementScaleSelection(float dS, vec3 scalingDir);
	void translateSelection(float dx, float dz);
	void deleteSelection();


	void drawBoundingBox(node_ptr node, mat4 ctx);

};

