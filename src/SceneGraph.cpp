#include "SceneGraph.h"

//Assumes nodes were siblings
void SceneGraph::stackFurniture(node_ptr parent, node_ptr newNode)
{
	mat4 parentH = parent->preMultiplyTransform(mat4(1.0f));
	mat4 childH = newNode->preMultiplyTransform(mat4(1.0f));
	mat4 pHInv = glm::inverse(parentH);

	//TODO: Recursively undo transforms
	mat4 result = pHInv*childH;//Calculate new matrix before stacking translation
	result[3].y = 0;

	BoundingBox bb = parent->getBoundingBox();

	float stackHeight = bb.getAABBMax().y-bb.getAABBMin().y;//-bb.getAABBMin().y;//parent->getHeight(mat4(1.0f));
	//Undo parent transform to bring back 
	vec4 scaledHeight = inverse(childH)*vec4(0, stackHeight, 0, 0);
	scaledHeight.w = 1;
	result = translate(result, vec3(scaledHeight));
	//result[3] += scaledHeight;
	newNode->setTransform(result);
	parent->addChild(newNode);
}

//Helper function
void SceneGraph::addFurniture(string line)
{
	node_ptr newPiece;//Get reference to correct piece of furniture
	if(strcmp(line.c_str(), "lamp")==0){
		cout << "Adding Lamp..." << endl;
		newPiece = FurnitureFactory::makeLamp();
	}else if(strcmp(line.c_str(), "table")==0){
		cout << "Adding Table..." << endl;
		newPiece = FurnitureFactory::makeTable();
	}else if(strcmp(line.c_str(), "chair")==0){
		cout << "Adding Chair..." << endl;
		newPiece = FurnitureFactory::makeChair();
	}else if(strcmp(line.c_str(), "cabinet")==0){
		cout << "Adding Cabinet..." << endl;
		newPiece = FurnitureFactory::makeCabinet();
	}else{
		cout << "Error, unknown furniture type" <<endl;
		exit(1);
	}

	//Read R G B
	safeGetline(fp_in,line);
	vector<string> tokens = tokenizeString(line);
	vec3 rgb;
	rgb.r = atof(tokens[0].c_str());
	rgb.g = atof(tokens[1].c_str());
	rgb.b = atof(tokens[2].c_str());

	//Read xIndex, zIndex
	safeGetline(fp_in,line);
	tokens = tokenizeString(line);
	float xIndex = atof(tokens[0].c_str());
	float zIndex = atof(tokens[1].c_str());

	//Read rotation
	safeGetline(fp_in,line);
	float rotation = atof(line.c_str());

	//Read xscale yscale zscale 
	safeGetline(fp_in,line);
	tokens = tokenizeString(line);
	vec3 scale;
	scale.x = atof(tokens[0].c_str());
	scale.y = atof(tokens[1].c_str());
	scale.z = atof(tokens[2].c_str());

	mat4 transform = mat4(1.0f);
	transform = translate(transform, vec3(xIndex, 0, zIndex));
	transform = rotate(transform, rotation, vec3(0,1,0));
	transform = glm::scale(transform, scale);

	//Assemble new node
	node_ptr newNode = node_ptr(new Node(transform, rgb, newPiece));

	//Add at top level, will rebalance down if collisions detected.
	insertNode(root, newNode);
}

//Internally resolves collisions
void SceneGraph::insertNode(node_ptr parent, node_ptr newNode){
	parent->addChild(newNode);

	resolveCollisions(parent);
}

//Internally resolves collisions by recursively "rebalancing" tree
void SceneGraph::resolveCollisions(node_ptr parent){
	node_ptr c1_out, c2_out;
	while(findFirstCollisionXY(parent, c1_out, c2_out))
	{
		//TODO Resolve collisions
		//stack c2 on c1 and recurse
		parent->removeChild(c2_out);
		stackFurniture(c1_out, c2_out);
		resolveCollisions(c1_out);
	}

}

bool checkCollision(mat4 modelView, node_ptr node, float xPos, float zPos)
{
	//Push transform
	modelView = node->preMultiplyTransform(modelView);

	for(vector<node_ptr>::iterator it = node->mChildren.begin(); it != node->mChildren.end(); ++it) {
		bool collision = checkCollision(modelView, *it, xPos, zPos);
		if(collision != NULL)
			return collision;//TODO: Write this as a separate function
	}
	//First node with geometry is assumed to be in model space
	if(node->hasGeometry())
	{
		if(epsilonCheckEqual(modelView[3].x,xPos, 0.5) &&  epsilonCheckEqual(modelView[3].z,zPos,0.5) )
		{
			return true;
		}
	}
	return false;
}

//Checks for any collisions between children of a parent node.
//Returns the first collision encountered
bool SceneGraph::findFirstCollisionXY(node_ptr parent, node_ptr& c1_out, node_ptr& c2_out)
{
	//For each child of parent
	for(vector<node_ptr>::iterator it = parent->mChildren.begin(); it != parent->mChildren.end(); ++it) {
		c1_out = *it;//Outer loop collision
		vec4 c1_origin = c1_out->getOrigin();

		for(vector<node_ptr>::iterator it2 = it+1; it2 != parent->mChildren.end(); ++it2) {
			c2_out = *it2;//Inner loop collision
			//if collision between these two
			if(checkCollision(mat4(1.0f), c2_out, c1_origin.x, c1_origin.z))
			{
				return true;
			}
		}
	}
	return false;
}



SceneGraph::SceneGraph(string filename)
{
	//TODO: load scene in constructor.
	cout << "Reading scene from " << filename << " ..." << endl;

	char* fname = (char*)filename.c_str();
	fp_in.open(fname);
	if(fp_in.is_open()){

		//Read first line
		if(fp_in.good()){
			string line;
			safeGetline(fp_in,line);
			if(!line.empty()){
				vector<string> tokens = tokenizeString(line);
				xSize = atoi(tokens[0].c_str())+1;
				zSize = atoi(tokens[1].c_str())+1;
				numItems = atoi(tokens[2].c_str());//Not really important
			}
		}
		printf("Scene Size: (%d, %d), Num Items: %d\n", xSize, zSize, numItems);


		//Initialize graph and add floor
		mat4 modelView = mat4(1.0f);
		//Offset a bit to make scene appear grid centered
		modelView = translate(modelView, vec3(+0.5,0,+0.5));
		//indexes now perfectly line up with correct grid
		root = node_ptr(new Node(modelView, vec3(-1,-1,-1), node_ptr(new Floor(xSize,zSize))));

		//Load furniture one at a time
		while(fp_in.good())
		{
			string line;
			safeGetline(fp_in,line);
			if(!line.empty()){
				addFurniture(line);
			}
		}
	}else{
		//ERROR File not opened
		cout<<"Error, could not open file"<<endl;
		exit(1);
	}

	//Reset Traversal
	resetTraversal();
}


SceneGraph::~SceneGraph(void)
{
	//TODO: Handle memory release gracefully to avoid memory leaks.
}


void SceneGraph::draw(void)
{
	//Use default color magenta to make it stand out
	if(root != NULL){
		root->draw(mat4(1.0f), vec3(1,0,1));//Start with implicit identity transformation. 

		if(!mTraversalStack.empty()){
			TraversalState state = mTraversalStack.top();
			drawBoundingBox(state.node, state.contextView);
		}
	}
}

void SceneGraph::printGraph(void)
{
	if(root != NULL)
		root->print(0);
}


void SceneGraph::resetTraversal(void)
{
	//Reset stack
	mTraversalStack = stack<TraversalState>();

	//Push root
	mTraversalStack.push(TraversalState(root, mat4(1.0f)));
}

void SceneGraph::stepTraversal(void)
{
	if(mTraversalStack.empty())
	{
		resetTraversal();
	}

	TraversalState state = mTraversalStack.top();
	mTraversalStack.pop();

	mat4 newCtx = state.node->preMultiplyTransform(state.contextView);
	for(vector<node_ptr>::iterator it = state.node->mChildren.begin(); it != state.node->mChildren.end(); ++it) {
		//Push each child
		mTraversalStack.push(TraversalState(*it, newCtx));
	}


	if(mTraversalStack.empty())
	{
		resetTraversal();
	}

}

void SceneGraph::drawBoundingBox(node_ptr node, mat4 ctx)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	BoundingBox bb = node->getBoundingBox();

	//Figure out cube transform
	vec4 center = (bb.getAABBMax()+bb.getAABBMin())/2.0f;

	mat4 trans = translate(mat4(1.0f), vec3(center));
	mat4 scale = glm::scale(mat4(1.0f), 2.0f*vec3(bb.getAABBMax()-center));
	mat4 H = trans*scale;
	node_ptr bb_draw_node = node_ptr(new Node(H, vec3(1,0,0), GeometryFactory::makeCube()));
	bb_draw_node->draw(ctx, vec3(0,1,0));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void SceneGraph::rotateSelection(float deg)
{
	TraversalState selection = mTraversalStack.top();
	mat4 original = selection.node->getTransform();

	//Translate to origin
	vec4 translation = original[3];
	original[3] = vec4(0,0,0,1);
	original = glm::rotate(mat4(1.0f), deg, vec3(0,1,0))*original;
	//Restore
	original[3] = translation;
	selection.node->setTransform(original);

}

void SceneGraph::incrementScaleSelection(float dS, vec3 scalingDir)
{
	TraversalState selection = mTraversalStack.top();
	mat4 original = selection.node->getTransform();

	//Translate to origin
	vec4 translation = original[3];
	original[3] = vec4(0,0,0,1);

	vec4 scaling = original*vec4(scalingDir,0);

	mat4 scale = glm::scale(mat4(1.0f), normalize(vec3(scaling))*dS);

	original = original+scale;

	//Restore
	original[3] = translation;
	selection.node->setTransform(original);
}


void SceneGraph::translateSelection(float dx, float dz)
{
	TraversalState selection = mTraversalStack.top();
	mat4 original = selection.node->getTransform();

	//Translate to new location
	original[3] += vec4(dx,0,dz,0);
	selection.node->setTransform(original);


	resolveCollisions(root);
}

void SceneGraph::deleteNode(node_ptr node)
{
	resetTraversal();
	bool done = false;
	while(!mTraversalStack.empty() && !done){
		TraversalState state = mTraversalStack.top();
		mTraversalStack.pop();

		mat4 newCtx = state.node->preMultiplyTransform(state.contextView);
		for(vector<node_ptr>::iterator it = state.node->mChildren.begin(); it != state.node->mChildren.end(); ++it) {
			//Push each child unless it's the node we're deleting
			if(*it == node)
			{
				done = true;
			}else{
				mTraversalStack.push(TraversalState(*it, newCtx));
			}
		}
		if(done)
		{
			state.node->removeChild(node);
		}
	}

}

void SceneGraph::deleteSelection()
{
	TraversalState selection = mTraversalStack.top();
	deleteNode(selection.node);
}