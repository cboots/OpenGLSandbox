#pragma once

#include "glew.h"
#include <cstdlib>
#include <stdio.h>

using namespace std;


#define PI                          3.1415926535897932384626422832795028841971
#define TWO_PI                      6.2831853071795864769252867665590057683943
#define EPSILON                     .0000001

#define MIN(a,b)	((a<b)?a:b)
#define MAX(a,b)	((a>b)?a:b)
#define SWAP(x,y,t)    {t=x;x=y;y=t;}
#define MIN_POSITIVE(a,b) ((a >= 0)  ?  ((b >= 0)?((a < b)?a:b):a)  : ((b >= 0)?b:-1))
#define SIGN(a) ((a > 0)?1:((a < 0)?-1:0))



namespace Utility {

	typedef struct {
		GLuint vertex;
		GLuint fragment;
	} shaders_t;



shaders_t loadShaders(const char * vert_path, const char * frag_path);

void attachAndLinkProgram( GLuint program, shaders_t shaders);

char* loadFile(const char *fname, GLint &fSize);

// printShaderInfoLog
// From OpenGL Shading Language 3rd Edition, p215-216
// Display (hopefully) useful error messages if shader fails to compile
void printShaderInfoLog(GLint shader);

void printLinkInfoLog(GLint prog) ;
}
 