#ifndef MODIFIEDHENYEYMATRIXINVERSION_H
#define MODIFIEDHENYEYMATRIXINVERSION_H

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
#include "subtractMatrix.h"
#include "matrixMultiply.h"
#include "matrixDivide.h"
#include "convert_to_vec2d.h"
#include "convert_from_vec2d.h"
#include "FindMax.h"
#include "G1J.h"
#include "G2J.h"
#include "G3J.h"
#include "G4J.h"
#include "PartialDeriv.h"
#include <float.h>
#include "matrixInvert.h"
#include "cleanMatrix.h"
#include "fourbyfourinvert.h"
#include "ReadInArray.h"
#include "FindNonZeroMax.h"
using namespace std;
void modifiedHenyeyMatrixInversion(struct bundle &vars, vec3d &C, vec3d &D, vec3d &E, vec2d &G, string iterNum);


#endif
