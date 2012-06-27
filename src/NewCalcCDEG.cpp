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
#include "FindNonZeroMax.h"
#include "G1J.h"
#include "G2J.h"
#include "G3J.h"
#include "G4J.h"
#include <float.h>


using namespace std;

void NewCalcCDEG(bundle &vars)
{
  OneD G1(jMax), G2(jMax), G3(jMax), G4(jMax);
  vec3d C(jMax,iMax,kMax), D(jMax,iMax,kMax), E(jMax,iMax,kMax);
  double epsilon = 1e-5;
  double dP, dr, dL, dT;

  C[0] = vec2d(4,4,0);
  E[jMax-1] = vec2d(4,4,0);

  for (int j = 0; j < jMax ; j++)
    {
        // Calculate the regular G's:
      G1[j] = G1J(vars,j);
      G2[j] = G2J(vars,j);
      G3[j] = G3J(vars,j);
      G4[j] = G4J(vars,j);
    }
  
  for (j = 0; j < jMax; j++)
    {
      dP = epsilon * (vars.P[j+1] - vars.P[j]);
      vars.P[j]+= dP;
      vars.eos_var_update(j);
      D[j][0][0] = (G1[j] - G1J(vars,j) ) / dP;
      D[j][1][0] = (G2[j] - G2J(vars,j) ) / dP;
      D[j][2][0] = (G3[j] - G3J(vars,j) ) / dP ;
      D[j][3][0] = (G4[j] - G4J(vars,j) ) / dP;
      if (j < jMax-1)
	{
	  C[j+1][0][0] = (G1[j+1] - G1J(vars,j+1) ) / dP;
	  C[j+1][1][0] = (G1[j+1] - G1J(vars,j+1) ) / dP;
	  C[j+1][2][0] = (G1[j+1] - G1J(vars,j+1) ) / dP;
	  C[j+1][3][0] = (G1[j+1] - G1J(vars,j+1) ) / dP;
	}
      vars.P[j]-= dP;

      dr = epsilon * (vars.r[j+1] - vars.r[j]);
      vars.r[j]+= dr;
      vars.eos_var_update(j);  // Note: this update will operate on the new r value, and the original P value at that location
      D[j][0][1] = (G1[j] - G1J(vars,j) ) / dr;
      D[j][1][1] = (G2[j] - G2J(vars,j) ) / dr;
      D[j][2][1] = (G3[j] - G3J(vars,j) ) / dr;
      D[j][3][1] = (G4[j] - G4J(vars,j) ) / dr;
      vars.r[j]-= dr;

      dL = epsilon * (vars.L[j+1] - vars.L[j]);
      vars.L[j]+= dL;
      vars.eos_var_update(j);
      D[j][0][2] = (G1[j] - G1J(vars,j) ) / dL;
      D[j][1][2] = (G2[j] - G2J(vars,j) ) / dL ;
      D[j][2][2] = (G3[j] - G3J(vars,j) ) / dL;
      D[j][3][2] = (G4[j] - G4J(vars,j) ) / dL;
      vars.L[j]-= dL;

      dT = epsilon * (vars.T[j+1] - vars.T[j]);
      vars.T[j]+= dT;
      vars.eos_var_update(j);
      D[j][0][3] = (G1[j] - G1J(vars,j) ) / dT;
      D[j][1][3] = (G2[j] - G2J(vars,j) ) / dT;
      D[j][2][3] = (G3[j] - G3J(vars,j) ) / dT;
      D[j][3][3] = (G4[j] - G4J(vars,j) ) / dT;
      vars.T[j]-=dT;
      vars.eos_var_update(j);
    }


}
