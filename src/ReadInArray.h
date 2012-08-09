#ifndef READINARRAY_H
#define READINARRAY_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>
#include <float.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "printVector.h"
#include "printMatrix.h"
using namespace std;

OneD ReadInArray(string filename, int xSize);
vec2d ReadInArray(string filename, int xSize, int ySize);
vec3d ReadInArray(string filename, int xSize, int ySize, int zSize);



#endif
