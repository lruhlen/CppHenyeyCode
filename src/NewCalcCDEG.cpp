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

void NewCalcCDEG(bundle &vars, vec2d &myG, vec3d &myC, vec3d &myD, vec3d &myE)
{

  OneD G1(jMax), G2(jMax), G3(jMax), G4(jMax);
  vec3d C(jMax,iMax,kMax,0), D(jMax,iMax,kMax,0), E(jMax,iMax,kMax,0);
  //  double epsilon = 1e-5;
  double epsilon = 5e-9;
  double dP, dr, dL, dT;



  //  for (int j = 0; j < jMax -1 ; j++)
  for (int j=0; j < jMax; j++)
    {
        // Calculate the regular G's:
      G1[j] = G1J(vars,j);
      G2[j] = G2J(vars,j);
      G3[j] = G3J(vars,j);
      G4[j] = G4J(vars,j);
      myG[j][0] = G1[j];
      myG[j][1] = G2[j];
      myG[j][2] = G3[j];
      myG[j][3] = G4[j];
    }
  OneD originalAtm(5);
  originalAtm = atmos(vars.r[jMax-1], vars.L[jMax-1], vars.dMwhole[jMax-1],vars.Mwhole[jMax-1], vars.EOS);
  double Rorig = originalAtm[1], Porig = originalAtm[2], Torig = originalAtm[3], Rhoorig = originalAtm[4];
  myG[jMax-1][0] = vars.P[jMax-1] - Porig;
  myG[jMax-1][1] = vars.r[jMax-1]-vars.r[jMax-2] - Rorig;
  myG[jMax-1][2] = vars.L[jMax-1] - vars.L[jMax-2];
  myG[jMax-1][3] = vars.T[jMax-1] - Torig;

  // cout<<"\nInputs to (unperturbed) atmos calcs:\n";
  // cout<<"R = "<<vars.r[jMax-1]<<endl;
  // cout<<"L = "<<vars.L[jMax-1]<<endl;
  // cout<<"dM = "<<vars.dMwhole[jMax-1]<<endl;
  // cout<<"M = "<<vars.Mwhole[jMax-1]<<endl;
  
  
  // Calculating the C/D/E derivatives  
  for (int j = 0; j < jMax; j++)
    {

      // Need to make sure you don't accidentally end up with dX = 0
      // because that'll give you NANs in your matrices, and that's not good.
      
      if (j+1 == jMax)
	{
	  dP = epsilon * (vars.P[j] + vars.P[j-1]);
	  dr = epsilon * (vars.r[j] + vars.r[j-1]);
	  dL = epsilon * (vars.L[j] + vars.L[j-1]);
	  dT = epsilon * (vars.T[j] + vars.T[j-1]);
	}
      else
	{
	  dP = epsilon * (vars.P[j+1] + vars.P[j]);
	  dr = epsilon * (vars.r[j+1] + vars.r[j]);
	  dL = epsilon * (vars.L[j+1] + vars.L[j]);
	  dT = epsilon * (vars.T[j+1] + vars.T[j]);
	}
      //      cout<<"j = "<<j<<"\tdP = "<<dP<<"\tdr = "<<dr<<"\tdL = "<<dL<<"\tdT = "<<dT<<endl;

      vars.P[j]+= dP;
      vars.eos_var_update(j);
 
      D[j][0][0] = (G1[j] - G1J(vars,j) ) / dP;
      D[j][1][0] = (G2[j] - G2J(vars,j) ) / dP;
      D[j][2][0] = (G3[j] - G3J(vars,j) ) / dP ;
      D[j][3][0] = (G4[j] - G4J(vars,j) ) / dP;
      if (j+1 < jMax-1)
	{
	  C[j+1][0][0] = (G1[j+1] - G1J(vars,j+1) ) / dP;
	  C[j+1][1][0] = (G2[j+1] - G2J(vars,j+1) ) / dP;
	  C[j+1][2][0] = (G3[j+1] - G3J(vars,j+1) ) / dP;
	  C[j+1][3][0] = (G4[j+1] - G4J(vars,j+1) ) / dP;
	}
      if (j > 0)
	{
	  E[j-1][0][0] = (G1[j-1] - G1J(vars,j-1) ) / dP;
	  E[j-1][1][0] = (G2[j-1] - G2J(vars,j-1) ) / dP;
	  E[j-1][2][0] = (G3[j-1] - G3J(vars,j-1) ) / dP;
	  E[j-1][3][0] = (G4[j-1] - G4J(vars,j-1) ) / dP;
	}
      vars.P[j]-= dP;

 
      vars.r[j]+= dr;
      vars.eos_var_update(j);  // Note: this update will operate on the new r value, and the original P value at that location
      D[j][0][1] = (G1[j] - G1J(vars,j) ) / dr;
      D[j][1][1] = (G2[j] - G2J(vars,j) ) / dr;
      D[j][2][1] = (G3[j] - G3J(vars,j) ) / dr;
      D[j][3][1] = (G4[j] - G4J(vars,j) ) / dr;
      if (j+1 < jMax-1)
	{
	  C[j+1][0][1] = (G1[j+1] - G1J(vars,j+1) ) / dr;
	  C[j+1][1][1] = (G2[j+1] - G2J(vars,j+1) ) / dr;
	  C[j+1][2][1] = (G3[j+1] - G3J(vars,j+1) ) / dr;
	  C[j+1][3][1] = (G4[j+1] - G4J(vars,j+1) ) / dr;
	}
      if (j > 0)
	{
	  E[j-1][0][1] = (G1[j-1] - G1J(vars,j-1) ) / dr;
	  E[j-1][1][1] = (G2[j-1] - G2J(vars,j-1) ) / dr;
	  E[j-1][2][1] = (G3[j-1] - G3J(vars,j-1) ) / dr;
	  E[j-1][3][1] = (G4[j-1] - G4J(vars,j-1) ) / dr;
	}
      vars.r[j]-= dr;


      vars.L[j]+= dL;
      vars.eos_var_update(j);
      D[j][0][2] = (G1[j] - G1J(vars,j) ) / dL;
      D[j][1][2] = (G2[j] - G2J(vars,j) ) / dL ;
      D[j][2][2] = (G3[j] - G3J(vars,j) ) / dL;
      D[j][3][2] = (G4[j] - G4J(vars,j) ) / dL;
      if (j+1 < jMax-1)
	{
	  C[j+1][0][2] = (G1[j+1] - G1J(vars,j+1) ) / dL;
	  C[j+1][1][2] = (G2[j+1] - G2J(vars,j+1) ) / dL;
	  C[j+1][2][2] = (G3[j+1] - G3J(vars,j+1) ) / dL;
	  C[j+1][3][2] = (G4[j+1] - G4J(vars,j+1) ) / dL;
	}
      if (j > 0)
	{
	  E[j-1][0][2] = (G1[j-1] - G1J(vars,j-1) ) / dL;
	  E[j-1][1][2] = (G2[j-1] - G2J(vars,j-1) ) / dL;
	  E[j-1][2][2] = (G3[j-1] - G3J(vars,j-1) ) / dL;
	  E[j-1][3][2] = (G4[j-1] - G4J(vars,j-1) ) / dL;
	}
      vars.L[j]-= dL;


      vars.T[j]+= dT;
      vars.eos_var_update(j);
      D[j][0][3] = (G1[j] - G1J(vars,j) ) / dT;
      D[j][1][3] = (G2[j] - G2J(vars,j) ) / dT;
      D[j][2][3] = (G3[j] - G3J(vars,j) ) / dT;
      D[j][3][3] = (G4[j] - G4J(vars,j) ) / dT;
      if (j+1 < jMax-1)
	{
	  C[j+1][0][3] = (G1[j+1] - G1J(vars,j+1) ) / dT;
	  C[j+1][1][3] = (G2[j+1] - G2J(vars,j+1) ) / dT;
	  C[j+1][2][3] = (G3[j+1] - G3J(vars,j+1) ) / dT;
	  C[j+1][3][3] = (G4[j+1] - G4J(vars,j+1) ) / dT;
	}
      if (j > 0)
	{
	  E[j-1][0][3] = (G1[j-1] - G1J(vars,j-1) ) / dT;
	  E[j-1][1][3] = (G2[j-1] - G2J(vars,j-1) ) / dT;
	  E[j-1][2][3] = (G3[j-1] - G3J(vars,j-1) ) / dT;
	  E[j-1][3][3] = (G4[j-1] - G4J(vars,j-1) ) / dT;
	}
      vars.T[j]-=dT;
      vars.eos_var_update(j);
    }

  // Evaluate the CDEG values at the outer (atmospheric) boundary
  int j = jMax-1;
  C[0] = vec2d(4,4,0);
  D[j] = vec2d(4,4,0);
  E[j] = vec2d(4,4,0);

  C = matrixMultiply(-1.0,C);
  D = matrixMultiply(-1.0,D);
  E = matrixMultiply(-1.0,E);

  C[j][1][1] = -1.0;
  C[j][2][2] = -1.0;
  D[j][0][0] = 1.0;
  D[j][2][2] = 1.0;
  D[j][3][3] = 1.0;

  OneD atConstL(5), atConstR(5);
  double Lnew = (1.0 + epsilon) * vars.L[j];
  double Rnew = (1.0 + epsilon) * vars.r[j];

  dL = epsilon * vars.L[j];
  dr = epsilon * vars.r[j];

  atConstL = atmos(Rnew, vars.L[j], vars.dMwhole[j],vars.Mwhole[j], vars.EOS);
  atConstR = atmos(vars.r[j], Lnew, vars.dMwhole[j],vars.Mwhole[j], vars.EOS);

  double RconstL = atConstL[1], PconstL = atConstL[2], TconstL = atConstL[3], RhoconstL = atConstL[4];
  double RconstR = atConstR[1], PconstR = atConstR[2], TconstR = atConstR[3], RhoconstR = atConstR[4];

  D[j][0][1] = ((PconstL - Porig) / dr) * -1.0;
  D[j][0][2] = ((PconstR - Porig) / dL) * -1.0;
  D[j][1][1] = (-1.0 + ( (RhoconstL -Rhoorig) / dr )) * -1.0;
  D[j][1][2] =  ((RhoconstR - Rhoorig) / dL) * -1.0;
  D[j][3][1] =  ((TconstL - Torig) / dr) * -1.0;
  D[j][3][2] =  ((RconstR - Rorig) / dL) * -1.0;

  // Set the 'return' values
  myC = C;
  myD = D;
  myE = E;
}
