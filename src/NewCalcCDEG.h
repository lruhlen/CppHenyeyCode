#ifndef NEWCALCCDEG_H
#define NEWCALCCDEG_H

#include <iostream>
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
#include "matrixMultiply.h"
#include "matrixTranspose.h"
#include "G1J.h"
#include "G2J.h"
#include "G3J.h"
#include "G4J.h"
#include "atmos.h"


using namespace std;
void NewCalcCDEG(bundle &vars, vec2d &myG, vec3d &myC, vec3d &myD, vec3d &myE);


#endif
