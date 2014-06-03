#ifndef NEWCALCCDEG_FLIP_H
#define NEWCALCCDEG_FLIP_H

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
void NewCalcCDEG_flip(bundle &vars, vec2d &myG, vec3d &myC, vec3d &myD, vec3d &myE);


#endif
