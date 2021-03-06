#ifndef UNFLATTENMATRIX_H
#define UNFLATTENMATRIX_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>
#include <float.h>
#include "global.h"
#include "printMatrix.h"

using namespace std;

vec2d unflattenMatrix(OneD &array, int i_index, int j_index);
vec3d unflattenMatrix(OneD &array, int i_index, int j_index, int k_index);

vec2d unflattenMatrix(vec2d &array, int i_index, int j_index);
vec3d unflattenMatrix(vec2d &array, int i_index, int j_index, int k_index);

#endif
