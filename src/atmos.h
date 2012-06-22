#ifndef ATMOS_H
#define ATMOS_H
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <vector>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
using namespace std;

OneD atmos(double &Rout, double &Lout, double &dM, double &Mstar, TableGroup &eos);


#endif

