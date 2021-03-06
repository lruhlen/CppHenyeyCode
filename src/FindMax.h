#ifndef FINDMAX_H
#define FINDMAX_H
#include "global.h"
#include <vector>

using namespace std;

double FindMax(struct vec3d &matrix);
double FindMax(struct vec2d &matrix);
double FindMax(vector<vector<double> > &matrix);
double FindMax(vector<double> &matrix);

#endif
