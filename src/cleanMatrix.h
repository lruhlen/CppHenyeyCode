#ifndef CLEANMATRIX_H
#define CLEANMATRIX_H
#include <vector>
#include <math.h>
#include <string.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "printMatrix.h"
#include "matrixMultiply.h"
#include "addMatrix.h" 
#include <float.h>

using namespace std;
vec3d cleanMatrix(struct vec3d matrix);
vec2d cleanMatrix(struct vec2d matrix);
vector<double> cleanMatrix(vector<double> matrix);
double cleanMatrix(double matrix);

#endif
