#include "Node.h"


Node::Node(void)
{
	init(mat4(1.0f), vec3(-1,-1,-1), node_ptr());
}

Node::Node(mat4 transform) 
{
	init(transform, vec3(-1,-1,-1), node_ptr());
}

Node::Node(mat4 transform, vec3 color)
{
	init(transform, color, node_ptr());
}

Node::Node(mat4 transform, vec3 color, node_ptr geom)
{
	init(transform, color, geom);
}

void Node::init(mat4 transform, vec3 color, node_ptr geom)
{
	this->mColor = color;
	this->mTransform = transform;
	mChildren = vector<node_ptr>();
	mGeometry = geom;
}


Node::~Node(void)
{
	//TODO: Handle memory release gracefully to avoid memory leaks.
}


mat4 Node::preMultiplyTransform(mat4 modelView)
{
	return  modelView*this->mTransform;
}

void Node::setTransform(mat4 transform)
{
	mTransform = transform;
}


mat4 Node::getTransform()
{
	return mTransform;
}


void Node::draw(mat4 modelView, vec3 rgb)
{
	//Apply node transform
	modelView = preMultiplyTransform(modelView);

	//If color change, apply that as well
	if(mColor.r >= 0 && mColor.g >= 0 && mColor.b >= 0
		&& mColor.r <= 1 && mColor.g <= 1 && mColor.b <= 1)
	{
		//Valid color
		rgb = mColor;
	}

	//This is a draw traversal, be sure to draw geometry.
	if(mGeometry != NULL)
	{
		mGeometry->draw(modelView, rgb);
	}

	for(int i = 0; i < mChildren.size(); i++)
	{
		//Recurse tree
		mChildren[i]->draw(modelView, rgb);
	}
}

void Node::addChild(node_ptr child){
	mChildren.push_back(child);
}


node_ptr Node::removeChild(node_ptr child){
	vector<node_ptr>::iterator it = find(mChildren.begin(), mChildren.end(), child);
	node_ptr val;
	if(it != mChildren.end())
	{
		val = *it;
		mChildren.erase(it);
	}
	return val;
}


void Node::setColor(vec3 rgb)
{
	mColor = rgb;
}


bool Node::hasGeometry()
{
	return mGeometry != NULL;
}


void Node::print(int depth)
{
	//Print tree depth
	for(int i = 0; i < depth - 1; i++)
	{
		printf("|");
	}

	if(depth > 0)
		printf("%c", 192);//hierarchy right angle

	//Print node info
	printf("%s, #C: %d, RGB: (%.2f, %.2f, %.2f), T: (%.2f,%.2f,%.2f)", this->getName().c_str(), mChildren.size(), mColor.r, mColor.g, mColor.b, mTransform[3].x, mTransform[3].y, mTransform[3].z);

	//printMat(mTransform);

	//New line
	printf("\n");
	if(mGeometry != NULL){
		mGeometry->print(depth+1);
	}
	//Print children recursively
	for(int i = 0; i < mChildren.size(); i++)
	{
		mChildren[i]->print(depth+1);
	}
}

string Node::getName()
{
	return "Node";
}


BoundingBox Node::getBoundingBox()
{
	BoundingBox bb = BoundingBox();

	if(mGeometry != NULL){
		string name = mGeometry->getName();
		bb = BoundingBox::Merge(bb, mGeometry->getBoundingBox());
	}

	//Merge in children bounding box
	for(vector<node_ptr>::iterator it = mChildren.begin(); it != mChildren.end(); ++it) {
		bb = BoundingBox::Merge(bb, (*it)->getBoundingBox());
	}

	return bb.preMultiplyBy(mTransform);
}

vec4 Node::getOrigin()
{
	return mTransform[3];
}