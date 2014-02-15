#include "Sphere.h"


Sphere::Sphere(void)
{
	cout<<"Initializing a Sphere Object. Should only happen Once"<<endl;

	
	rings  = 32;
	sectors = 32;

	//Implementation based on http://stackoverflow.com/questions/5988686/creating-a-3d-sphere-in-opengl-using-visual-c
	float radius = 0.5;
	float const R = 1./(float)(rings-1);
	float const S = 1./(float)(sectors-1);
	int r, s;

	vertices.resize(rings * sectors * 4);
	normals.resize(rings * sectors * 4);
	colors.resize(rings * sectors * 3);
	std::vector<float>::iterator v = vertices.begin();
	std::vector<float>::iterator n = normals.begin();
	for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
		float const y = glm::sin( -PI/2 + PI * r * R );
		float const x = glm::cos(2*PI * s * S) * glm::sin( PI * r * R );
		float const z = glm::sin(2*PI * s * S) * glm::sin( PI * r * R );


		*v++ = x * radius;
		*v++ = y * radius;
		*v++ = z * radius;
		*v++ = 1;

		*n++ = x;
		*n++ = y;
		*n++ = z;
		*n++ = 0;

	}

	indices.resize(rings * sectors * 6);
	std::vector<unsigned short>::iterator i = indices.begin();
	for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
		*i++ = r * sectors + s;
		*i++ = r * sectors + (s+1);
		*i++ = (r+1) * sectors + (s+1);

		*i++ = (r+1) * sectors + (s+1);
		*i++ = (r+1) * sectors + s;
		*i++ = r * sectors + s;
	}
	indices.resize(rings * sectors * 3);
	for(int i = 0; i < rings*sectors; i++)
	{

		colors[0+i*3] = 1;
		colors[1+i*3] = 1;
		colors[2+i*3] = 1;
	}

}

void Sphere::draw(mat4 modelView, vec3 rgb){

	//fill color buffer
	for(int i = 0; i < rings*sectors; i++)
	{
		colors[0+i*3] = rgb.r;//abs(normals[i*4+0]);
		colors[1+i*3] = rgb.g;//abs(normals[i*4+1]);
		colors[2+i*3] = rgb.b;//abs(normals[i*4+2]);
	}

	//now we put the data into the Vertex Buffer Object for the graphics system to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, rings*sectors*4*sizeof(float), &vertices[0], GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, rings*sectors*3*sizeof(float), &colors[0], GL_STREAM_DRAW);	

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, rings*sectors*4*sizeof(float), &normals[0], GL_STREAM_DRAW); 

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,  rings*sectors*2*3*sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);


	//set the modelview uniform
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &modelView[0][0]);

	//draw the elements
	glDrawElements(GL_TRIANGLES, rings*sectors*2*3, GL_UNSIGNED_SHORT, 0);

	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);
}

string Sphere::getName()
{
	return "Sphere";
}

BoundingBox Sphere::getBoundingBox()
{
	return BoundingBox::MakeCenteredUnitBox();
}