#ifndef MATRIXDIVIDE_H
#define MATRIXDIVIDE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "printVector.h"
#include "printMatrix.h"
#include "FindMax.h"
#include <float.h>
#include "cleanMatrix.h"

using namespace std;

vec3d matrixDivide(vec3d &matrixA, vec3d &matrixB);
vec2d matrixDivide(vec2d &matrixA, vec2d &matrixB);
vector<double> matrixDivide(vector<double> &matrixA, vector<double> &matrixB);
vec3d matrixDivide(double &A, vec3d &matrixB);
vec2d matrixDivide(double &A, vec2d &matrixB);
vector<double> matrixDivide(double &A, vector<double> &matrixB);


#endif
