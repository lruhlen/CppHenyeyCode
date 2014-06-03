#ifndef MAKEHENYEYMATRIX_H
#define MAKEHENYEYMATRIX_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "printVector.h"
#include "printMatrix.h"
#include "matrixTranspose.h"
#include "dotProduct.h"
#include "addMatrix.h"
#include "matrixMultiply.h"
#include "matrixDivide.h"
#include "convert_to_vec2d.h"
#include "convert_from_vec2d.h"
#include "FindMax.h"
#include <float.h>

vec2d MakeHenyeyMatrix(vec3d &C, vec3d &D, vec3d &E);


#endif
