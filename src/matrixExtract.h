#ifndef MATRIXEXTRACT_H
#define MATRIXEXTRACT_H

#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"

using namespace std;

OneD matrixExtract(vec2d &bigMatrix, int index);
vec2d matrixExtract(vec3d &bigMatrix, int index);

#endif
