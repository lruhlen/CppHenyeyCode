#ifndef CALCCDEGPRIME_H
#define CALCCDEGPRIME_H

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
#include "G1Jprime.h"
#include "G2Jprime.h"
#include "G3Jprime.h"
#include "G4Jprime.h"
#include <float.h>


using namespace std;
void CalcCDEGprime(bundle &vars, vec3d &Cprime, vec3d &Dprime, vec3d &Eprime, vec2d &Gprime);


#endif
