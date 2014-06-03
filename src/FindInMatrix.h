#ifndef FINDINMATRIX_H
#define FINDINMATRIX_H

#include <iostream>
#include <vector>
#include <math.h>
#include "global.h"
using namespace std;

vector<vector<int> > FindInMatrix(double val, vec3d &matrix);
vector<vector<int> > FindInMatrix(double val, vec2d &matrix);
vector<vector<int> > FindInMatrix(double val, vector<double> &matrix);



#endif
