#ifndef MATRIXMULTIPLY_H
#define MATRIXMULTIPLY_H
#include <iostream>
#include <vector>
#include "dotProduct.h"
#include "matrixTranspose.h"
#include "printVector.h"
#include "printMatrix.h"
#include "global.h"


using namespace std;

struct vec2d matrixMultiply(struct vec2d &matrixA, struct vec2d &matrixB);

vector< vector<double> > matrixMultiply(vector<vector <double> > &matrixA, vector< vector<double> > &matrixB);

OneD matrixMultiply(OneD &vectorA, struct vec2d &matrixB);

vector< vector<double> > matrixMultiply( vector<double> &vectorA, vector< vector<double> > &matrixB);

OneD matrixMultiply(struct vec2d &matrixA, OneD &vectorB);

vector< vector<double> > matrixMultiply( vector< vector<double> > &matrixA, vector<double>  &vectorB);
struct vec3d matrixMultiply(double constA, struct vec3d &matrixB);

struct vec2d matrixMultiply(double constA, struct vec2d &matrixB);

vector< vector<double> > matrixMultiply(double constA, vector< vector<double> > &matrixB);

struct vec3d matrixMultiply(struct vec3d &matrixB, double constA);

struct vec2d matrixMultiply(struct vec2d &matrixB, double constA);

vector< vector<double> > matrixMultiply(vector< vector<double> > &matrixB, double constA);

vector<double>  matrixMultiply(double constA, vector<double> &matrixB);

vector<double>  matrixMultiply( vector<double> &matrixB, double constA);

#endif

