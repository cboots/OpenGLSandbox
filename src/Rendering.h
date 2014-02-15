#pragma once
#include "glew.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../freeglut/include/GL/glut.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include "Utils.h"

using namespace glm;



//vertex arrays needed for drawing
extern unsigned int vbo;
extern unsigned int cbo;
extern unsigned int nbo;
extern unsigned int ibo;


//attributes
extern unsigned int positionLocation;
extern unsigned int colorLocation;
extern unsigned int normalLocation;

//uniforms
extern unsigned int u_lightPosLocation;
extern unsigned int u_modelMatrixLocation;
extern unsigned int u_projMatrixLocation;
	
//needed to compile and link and use the shaders
extern unsigned int vertexShader;
extern unsigned int fragmentShader;
extern unsigned int shaderProgram;

extern clock_t old;

extern glm::vec3 vertices[];
extern glm::vec3 normals[];
extern glm::vec3 colors[];
extern unsigned short indices[];

//helper function to read shader source and put it in a char array
//thanks to Swiftless
char* textFileRead(const char*);

//some other helper functions from CIS 565
void printLinkInfoLog(int);
void printShaderInfoLog(int);

//standard glut-based program functions
void initOpenGL(int argc, char** argv, int width, int height);
void initShaders(void);
void initVBOs(void);
void resize(int, int);
void cleanup(void);
