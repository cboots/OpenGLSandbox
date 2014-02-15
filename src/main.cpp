#include "glew.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../freeglut/include/GL/glut.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include "Rendering.h"
#include "SceneGraph.h"

using namespace glm;


SceneGraph* pScene;

void keypress(unsigned char, int, int);
void display(void);

int main(int argc, char** argv) {
	if(argc < 2)
	{
		cout << "Need to pass config file as argument" << endl;
		system("pause");
		exit(1);
	}

	//Load scene
	pScene = new SceneGraph(argv[1]);
	pScene->printGraph();


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Starter Code");

	//Call GLEW only _after_ you get the window
	//I had to tell the author of your textbook that ;-)  -Cory
	glewInit();

	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keypress);
	glutIdleFunc(display);


	glutMainLoop();
	return 0;
}


void display() {
	//Always and only do this at the start of a frame, it wipes the slate clean
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	clock_t newTime = clock();

	pScene->draw();

	glutSwapBuffers();
	old = newTime;
}



void keypress(unsigned char key, int x, int y) {
	switch(key) {
	case 'q':
		cleanup();
		exit(0);
		break;
	case 'n':
		pScene->stepTraversal();
		cout << "Traversal Advanced 1 Step"<<endl;
		break;
	case 'c':
		pScene->resetTraversal();
		cout << "Traversal Selection Cleared"<<endl;
		break;
	case 'r':
		pScene->rotateSelection(10.0f);
		cout << "Rotating Selection by 10 degrees" << endl;
		break;
	case 'R':
		pScene->rotateSelection(-10.0f);
		cout << "Rotating Selection by -10 degrees" << endl;
		break;
	case 'x':
		pScene->incrementScaleSelection(0.5, vec3(1,0,0));
		cout << "Increasing Selection X Scaling by 0.5" << endl;
		break;
	case 'X':
		pScene->incrementScaleSelection(-0.5, vec3(1,0,0));
		cout << "Decreasing Selection X Scaling by 0.5" << endl;
		break;
	case 'y':
		pScene->incrementScaleSelection(0.5, vec3(0,1,0));
		cout << "Increasing Selection Y Scaling by 0.5" << endl;
		break;
	case 'Y':
		pScene->incrementScaleSelection(-0.5, vec3(0,1,0));
		cout << "Decreasing Selection Y Scaling by 0.5" << endl;
		break;
	case 'z':
		pScene->incrementScaleSelection(0.5, vec3(0,0,1));
		cout << "Increasing Selection Z Scaling by 0.5" << endl;
		break;
	case 'Z':
		pScene->incrementScaleSelection(-0.5, vec3(0,0,1));
		cout << "Decreasing Selection Z Scaling by 0.5" << endl;
		break;
	case 'a':
		pScene->translateSelection(-0.5, 0);
		cout << "Translating Selection -0.5 in X" << endl;
		break;
	case 'd':
		pScene->translateSelection(0.5, 0);
		cout << "Translating Selection 0.5 in X" << endl;
		break;
	case 'w':
		pScene->translateSelection(0, 0.5);
		cout << "Translating Selection 0.5 in Z" << endl;
		break;
	case 's':
		pScene->translateSelection(0, -0.5);
		cout << "Translating Selection -0.5 in Z" << endl;
		break;
	case 'e':
		pScene->deleteSelection();
		cout << "Deleting Selection and Subtree" << endl;
		break;
	}

	glutPostRedisplay();
}
