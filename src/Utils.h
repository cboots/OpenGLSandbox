#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


#define PI                          3.1415926535897932384626422832795028841971
#define TWO_PI                      6.2831853071795864769252867665590057683943
#define EPSILON                     .0000001

#define MIN(a,b)	((a<b)?a:b)
#define MAX(a,b)	((a>b)?a:b)
#define SWAP(x,y,t)    {t=x;x=y;y=t;}
#define MIN_POSITIVE(a,b) ((a >= 0)  ?  ((b >= 0)?((a < b)?a:b):a)  : ((b >= 0)?b:-1))
#define SIGN(a) ((a > 0)?1:((a < 0)?-1:0))


extern bool epsilonCheckEqual(float a, float b, float ep);
extern std::istream& safeGetline(std::istream& is, std::string& t);
extern std::vector<std::string> tokenizeString(std::string str); 

// print out matrix by rows
void printMat(glm::mat4  mat);
