#include "Cylinder.h"


Cylinder::Cylinder(void)
{
	//TODO: Setup buffers
	cout<<"Initializing a Cylinder Object. Should only happen Once"<<endl;

	//Fill in vertices (first 2 are centers (bottom top), then bottom ring, 
	//then top ring, then bottom ring side, then top ring side)
	//Bottom center
	vertices[0] = 0; vertices[1] = -0.5; vertices[2] = 0; vertices[3] = 1;
	//Top center
	vertices[4] = 0; vertices[5] =  0.5; vertices[6] = 0; vertices[7] = 1;

	for(int i = 0; i < N; ++i)
	{
		float x = 0.5*glm::cos(float(i)/N*PI*2);
		float z = 0.5*glm::sin(float(i)/N*PI*2);

		int offset = 4*(2+i);
		vertices[offset + 0] = x; vertices[offset + 1] = -0.5; vertices[offset + 2] = z; vertices[offset + 3] = 1;
		offset += 4*N;
		vertices[offset + 0] = x; vertices[offset + 1] = +0.5; vertices[offset + 2] = z; vertices[offset + 3] = 1;
		offset += 4*N;
		vertices[offset + 0] = x; vertices[offset + 1] = -0.5; vertices[offset + 2] = z; vertices[offset + 3] = 1;
		offset += 4*N;
		vertices[offset + 0] = x; vertices[offset + 1] = +0.5; vertices[offset + 2] = z; vertices[offset + 3] = 1;
		offset += 4*N;
	}

	//Fill in normals
	//Bottom center
	normals[0] = 0; normals[1] = -1; normals[2] = 0; normals[3] = 0;
	//Top center
	normals[4] = 0; normals[5] =  1; normals[6] = 0; normals[7] = 0;
	for(int i = 0; i < N; ++i)
	{
		int offset = 4*(2+i);
		vec3 normal = normalize(vec3(vertices[offset+0], 0, vertices[offset+2]));
		normals[offset + 0] = 0; normals[offset + 1] = -1; normals[offset + 2] = 0; normals[offset + 3] = 0;
		offset += 4*N;
		normals[offset + 0] = 0; normals[offset + 1] = -1; normals[offset + 2] = 0; normals[offset + 3] = 0;

		offset += 4*N;
		normals[offset + 0] = normal.x; normals[offset + 1] =  normal.y; normals[offset + 2] =  normal.z; normals[offset + 3] = 0;
		offset += 4*N;
		normals[offset + 0] = normal.x; normals[offset + 1] =  normal.y; normals[offset + 2] =  normal.z; normals[offset + 3] = 0;

	}

	//Fill in colors
	for(int i = 0; i < (4*N+2); ++i)
	{
		colors[0+i*3] = 1;
		colors[1+i*3] = 1;
		colors[2+i*3] = 1;
	}

	//Build index buffer
	for(int i = 0; i < N; ++i)
	{
		int offset = 3*i;
		int v1 = i+2;
		int v2 = (i+1) % N + 2;
		//Bottom triangle
		indices[offset + 0] = 0; indices[offset + 1] = v1; indices[offset + 2] = v2;

		//Top triangle
		offset += 3*N;
		indices[offset + 0] = 1; indices[offset + 1] = v1+N; indices[offset + 2] = v2+N;

		//side triangles
		offset += 3*N;
		indices[offset + 0] = v1+2*N; indices[offset + 1] = v1+3*N; indices[offset + 2] = v2+3*N; 
		offset += 3*N;
		indices[offset + 0] = v2+3*N; indices[offset + 1] = v2+2*N; indices[offset + 2] = v1+2*N; 
		
	}

}



void Cylinder::draw(mat4 modelView, vec3 rgb){
	
	//fill color buffer
	for(int i = 0; i < (4*N+2); i++)
	{
		colors[0+i*3] = rgb.r;//abs(normals[i*4+0]);
		colors[1+i*3] = rgb.g;//abs(normals[i*4+1]);
		colors[2+i*3] = rgb.b;//abs(normals[i*4+2]);
	}

	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (4*N+2)*4*sizeof(float), vertices, GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, (4*N+2)*3*sizeof(float), colors, GL_STREAM_DRAW);	

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, (4*N+2)*4*sizeof(float), normals, GL_STREAM_DRAW); 

	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);

	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 4 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	//now use color data, remember we're not using 4 at a time anymore
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));

	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 4, GL_FLOAT, 0, 0, static_cast<char*>(0));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, N*4*3*sizeof(unsigned short), indices, GL_STATIC_DRAW);


	//set the modelview uniform
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &modelView[0][0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, 4*N*3, GL_UNSIGNED_SHORT, 0);

	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);
}



string Cylinder::getName()
{
	return "Cylinder";
}



BoundingBox Cylinder::getBoundingBox()
{
	return BoundingBox::MakeCenteredUnitBox();
}