#ifndef PRINTMATRIXTOFILE_H
#define PRINTMATRIXTOFILE_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include "global.h"
using namespace std;
void printMatrixToFile(FILE *outfile, vec3d &matrix);
void printMatrixToFile(FILE *outfile, vec2d &matrix);
void printMatrixToFile(FILE *outfile, OneD &matrix);

#endif
