#ifndef SUBTRACTMATRIX_H
#define SUBTRACTMATRIX_H
#include "global.h"
using namespace std;

struct vec3d subtractMatrix(struct vec3d &matrixA, struct vec3d &matrixB);

struct vec2d subtractMatrix(struct vec2d &matrixA, struct vec2d &matrixB);

struct vec2d subtractMatrix(struct vec2d &matrixA, vector<vector<double> > &matrixB);

struct vec2d subtractMatrix(vector<vector<double> > &matrixA, struct vec2d &matrixB);

vector<vector<double> > subtractMatrix(vector<vector<double> > &matrixA, vector<vector<double> > &matrixB );

vector<double> subtractMatrix(vector<double> &matrixA, vector<double> &matrixB );

struct vec3d subtractMatrix(struct vec3d &matrixA, double number);

struct vec3d subtractMatrix(double number, struct vec3d &matrixA);

struct vec2d subtractMatrix(struct vec2d &matrixA, double number);

struct vec2d subtractMatrix(double number, struct vec2d &matrixA);

vector<double> subtractMatrix(vector<double> &matrixA, double number );

vector<double> subtractMatrix(double number, vector<double> &matrixA);
OneD subtractMatrix(OneD &matrixA, vec2d &matrixB);
OneD subtractMatrix(vec2d &matrixA, OneD &matrixB);

#endif
