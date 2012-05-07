#ifndef ADDMATRIX_H
#define ADDMATRIX_H
#include "global.h"
using namespace std;

struct vec3d addMatrix(struct vec3d &matrixA, struct vec3d &matrixB);

struct vec2d addMatrix(struct vec2d &matrixA, struct vec2d &matrixB);

struct vec2d addMatrix(struct vec2d &matrixA, vector<vector<double> > &matrixB);

struct vec2d addMatrix(vector<vector<double> > &matrixA, struct vec2d &matrixB);

vector<vector<double> > addMatrix(vector<vector<double> > &matrixA, vector<vector<double> > &matrixB );

vector<double> addMatrix(vector<double> &matrixA, vector<double> &matrixB );

struct vec3d addMatrix(struct vec3d &matrixA, double number);

struct vec3d addMatrix(double number, struct vec3d &matrixA);

struct vec2d addMatrix(struct vec2d &matrixA, double number);

struct vec2d addMatrix(double number, struct vec2d &matrixA);

vector<double> addMatrix(vector<double> &matrixA, double number );

vector<double> addMatrix(double number, vector<double> &matrixA);

#endif
