#include "glew.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../freeglut/include/GL/glut.h"
#include <time.h>
#include "Rendering.h"

using namespace std;
using namespace glm;

void keypress(unsigned char, int, int);
void display(void);

int main(int argc, char** argv) {

	//Setup OpenGL Context
	initOpenGL(argc, argv, 640, 480);

	//Setup OpenGL callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keypress);
	glutIdleFunc(display);

	//Initalize virtual buffer objects.
	initVBOs();

	//Initialize shader programs
	initShaders();

	//Force resize to setup projection matrix 
	resize(640, 480);

	//Run main loop (repeatedly calls display and other callbacks)
	glutMainLoop();
	return 0;
}


void display() {
	clock_t newTime = clock();

	//Always and only do this at the start of a frame, it wipes the slate clean
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(float), &vertices[0][0], GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(float), &colors[0][0], GL_STREAM_DRAW);	

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(float), &normals[0][0], GL_STREAM_DRAW); 

	//activate our three kinds of information
	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(normalLocation);

	//we're using the vertex data first
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//define how the vertex pointer should work, in our case we're accessing floats 3 at a time with no special pattern
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));

	//now use color data
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));

	//one more time with the normals
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, 0, 0, static_cast<char*>(0));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*2*3*sizeof(unsigned short), indices, GL_STATIC_DRAW);


	mat4 modelView(1.0f);//identity

	

	//Always remember that it doesn't do much good if you don't have OpenGL actually use the shaders
	glUseProgram(shaderProgram);
	//set the modelview uniform
	glUniformMatrix4fv(u_modelMatrixLocation, 1, GL_FALSE, &modelView[0][0]);

	//draw the elements (6 is number of indecies, not triangles)
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	//shut off the information since we're done drawing
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(colorLocation);
	glDisableVertexAttribArray(normalLocation);



	glutSwapBuffers();
	old = newTime;
}



void keypress(unsigned char key, int x, int y) {
	switch(key) {
	case 'q':
		cleanup();
		exit(0);
		break;
	case 'r':

		cout << "Reloading shaders" << endl;
		initShaders();
		break;
	}

	glutPostRedisplay();
}
