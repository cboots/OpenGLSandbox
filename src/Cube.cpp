#include "Cube.h"

Cube::Cube()
{
	//Init buffers for cube
	cout<<"Initializing a Cube Object. Should only happen Once"<<endl;

	//We need 24 vertices total
	for(int i = 0; i < 3; i++)
	{
		int offset = 4*8*i;

		//Init point locations
		vertices[ 0+offset] = 0.5; vertices[ 1+offset] = 0.5; vertices[ 2+offset] = 0.5; vertices[ 3+offset] = 1;
		vertices[ 4+offset] = 0.5; vertices[ 5+offset] = 0.5; vertices[ 6+offset] =-0.5; vertices[ 7+offset] = 1;
		vertices[ 8+offset] = 0.5; vertices[ 9+offset] =-0.5; vertices[10+offset] = 0.5; vertices[11+offset] = 1;
		vertices[12+offset] = 0.5; vertices[13+offset] =-0.5; vertices[14+offset] =-0.5; vertices[15+offset] = 1;
		vertices[16+offset] =-0.5; vertices[17+offset] = 0.5; vertices[18+offset] = 0.5; vertices[19+offset] = 1;
		vertices[20+offset] =-0.5; vertices[21+offset] = 0.5; vertices[22+offset] =-0.5; vertices[23+offset] = 1;
		vertices[24+offset] =-0.5; vertices[25+offset] =-0.5; vertices[26+offset] = 0.5; vertices[27+offset] = 1;
		vertices[28+offset] =-0.5; vertices[29+offset] =-0.5; vertices[30+offset] =-0.5; vertices[31+offset] = 1;
	}


	//setup normals
	for(int j = 0; j < 8; j++)
	{
		//for each corner, assign the three normals
		//x normal faces
		int offset = j*4;
		normals[0+offset] = SIGN(vertices[0+offset]); normals[1+offset] = 0;  normals[2+offset] = 0;  normals[3+offset] = 0;

		//y normal faces
		offset+=4*8;
		normals[0+offset] = 0; normals[1+offset] = SIGN(vertices[1+offset]);  normals[2+offset] = 0;  normals[3+offset] = 0;

		//z normal faces
		offset+=4*8;
		normals[0+offset] = 0; normals[1+offset] = 0;  normals[2+offset] = SIGN(vertices[2+offset]);  normals[3+offset] = 0;
	}

	//Setup indices
	//+x face
	indices[ 0] = 0; indices[ 1] = 2; indices[ 2] = 1; indices[ 3] = 1; indices[ 4] = 2; indices[ 5] = 3;
	//-x face
	indices[ 6] = 6; indices[ 7] = 4; indices[ 8] = 7; indices[ 9] = 7; indices[10] = 4; indices[11] = 5;

	//+y face
	indices[12] = 8+0; indices[13] = 8+1; indices[14] = 8+4; indices[15] = 8+4; indices[16] = 8+1; indices[17] = 8+5;
	//-y face
	indices[18] = 8+7; indices[19] = 8+3; indices[20] = 8+6; indices[21] = 8+6; indices[22] = 8+3; indices[23] = 8+2;

	//+z face
	indices[24] = 16+0; indices[25] = 16+4; indices[26] = 16+2; indices[27] = 16+2; indices[28] = 16+4; indices[29] = 16+6;
	//-z face
	indices[30] = 16+1; indices[31] = 16+3; indices[32] = 16+5; indices[33] = 16+5; indices[34] = 16+3; indices[35] = 16+7;

	for(int i = 0; i < 24; i++)
	{
		colors[0+i*3] = 1;
		colors[1+i*3] = 1;
		colors[2+i*3] = 1;
	}

}

void Cube::draw(mat4 modelView, vec3 rgb){

	//fill color buffer
	for(int i = 0; i < 24; i++)
	{

		colors[0+i*3] = rgb.r;//abs(normals[i*4+0]);
		colors[1+i*3] = rgb.g;//abs(normals[i*4+1]);
		colors[2+i*3] = rgb.b;//abs(normals[i*4+2]);
	}

	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24*4*sizeof(float), vertices, GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, 24*3*sizeof(float), colors, GL_STREAM_DRAW);	

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, 24*4*sizeof(float), normals, GL_STREAM_DRAW); 

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*2*3*sizeof(unsigned short), indices, GL_STATIC_DRAW);


	//set the modelview uniform
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &modelView[0][0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);
}


string Cube::getName(){
	return "Cube";
}

BoundingBox Cube::getBoundingBox()
{
	return BoundingBox::MakeCenteredUnitBox();
}