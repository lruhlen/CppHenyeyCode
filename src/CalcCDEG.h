#ifndef CALCCDEG_H
#define CALCCDEG_H

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
#include "matrixDivide.h"
#include "FindMax.h"
#include "G1J.h"
#include "G2J.h"
#include "G3J.h"
#include "G4J.h"
#include <float.h>


using namespace std;
void CalcCDEG(bundle &vars, vec3d &C, vec3d &D, vec3d &E, vec2d &G);


#endif
