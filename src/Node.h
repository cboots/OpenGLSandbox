#pragma once
#include "../glm/glm.hpp"
#include <vector>
#include <algorithm>    // std::find
#include "Utils.h"
#include "BoundingBox.h"

using namespace glm;
using namespace std;

class Node;

typedef shared_ptr<Node> node_ptr;


class Node
{
protected:
	mat4 mTransform;
	vec3 mColor;
	node_ptr mGeometry;//Geometry is a special case of children that can be safely ignored for most traversals except drawing.
	
public:
	vector<node_ptr> mChildren;	//Public for convenience. TODO: Proper access
	Node(void);
	Node(mat4 transform);
	Node(mat4 transform, vec3 color);
	Node(mat4 transform, vec3 color, node_ptr geom);
	~Node(void);
	void init(mat4 transform, vec3 color, node_ptr geom);
	
	virtual void draw(mat4, vec3 );

	void addChild(node_ptr);
	node_ptr removeChild(node_ptr child);
	void setColor(vec3);
	mat4 preMultiplyTransform(mat4);
	bool hasGeometry();

	void setTransform(mat4);
	mat4 getTransform();

	virtual void print(int depth);
	virtual string getName();
	virtual BoundingBox getBoundingBox();
	virtual vec4 getOrigin();
};

