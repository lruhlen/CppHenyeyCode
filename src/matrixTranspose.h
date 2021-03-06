#ifndef MATRIXTRANSPOSE_H
#define MATRIXTRANSPOSE_H

#include <iostream>
#include <vector>
#include "printMatrix.h"
#include "global.h"
using namespace std;

struct vec2d matrixTranspose(struct vec2d &matrix); 
vector<vector<double> > matrixTranspose(vector< vector<double> > &matrix); 
//vector<vector<double> > matrixTranspose( vector<double> &matrix); 
//OneD matrixTranspose(vec2d &matrix);
vec2d matrixTranspose(OneD &matrix);

#endif
