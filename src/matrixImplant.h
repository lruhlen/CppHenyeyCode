#ifndef MATRIXIMPLANT_H
#define MATRIXIMPLANT_H

#include <vector>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"

using namespace std;

void matrixImplant(OneD &smallMatrix, vec2d &bigMatrix, int index);
void matrixImplant(vec2d &smallMatrix, vec3d &bigMatrix, int index);


#endif
