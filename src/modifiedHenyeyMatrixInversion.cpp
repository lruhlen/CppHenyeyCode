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
#include "matrixMultiply.h"
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
using namespace std;


void modifiedHenyeyMatrixInversion(struct bundle &vars, vec3d C, vec3d D, vec3d E, vec2d G)
{
  int moose;

  OneD TempG(iMax), TempA(iMax), TempSum(iMax), Tempdr(iMax), TempdP(iMax), TempdT(iMax), TempdL(iMax);

  vec2d A(jMax,iMax), TempB(iMax,iMax,0), TempC(iMax,iMax,0), TempD(iMax,iMax,0), TempE(iMax,iMax,0);

  vec2d TempInverseS(iMax,iMax,0), TempS(iMax,iMax,0), Sum(jMax,iMax);

  
  vec3d S(jMax,iMax,iMax), B(jMax,iMax,iMax), InverseS(jMax,iMax,iMax); 

  string continueHit;

  //-----------------------------------------------------------
  // Forward-bootstrap the A and B values from j=0 to j=jMax-1
  //-----------------------------------------------------------
  for (int j=0; j<jMax; j++)
    {
 	  TempG = G[j];
	  TempC = C[j];
	  TempD = D[j];
	  TempE = E[j];

	  // Start with the j=0 special case
	  if (j==0)
	    {
	      TempS = TempD;
	      TempSum = TempG;
	    }
	  else // Fill this case in latter...
	    {
	      /* Remember, neither TempA nor TempB have 
		 yet been updated from their values 
		 at the j-1 index
		 at this point, which is why we can use
		 them without any further updating or
		 variable shuffling in the calculations 
		 below.
	       */
	      vec2d foo = matrixMultiply(TempC,TempB);
	      TempS = addMatrix(foo,TempD);
	      vec2d baz = matrixInvert(TempS);
	      TempInverseS = matrixMultiply(-1.0,baz);
	      OneD bar = matrixMultiply(TempC,TempA);
	      TempSum = addMatrix(TempG,bar);
	      
	    }	  	  	  

	  /*
	    Here, TempA and TempB are updated to reflect
	    their values at the _current_ j index.	    
	   */
	  TempA = matrixMultiply(TempInverseS,TempSum);
	  TempB = matrixMultiply(TempInverseS,TempE);

	  A[j] = TempA;
	  Sum[j] = TempSum;
	  B[j] = TempB;
	  S[j] = TempS;
	  InverseS[j] = TempInverseS;
    }
  


  /*
    Solve for the dx surface values
  */
  OneD holder = matrixMultiply(TempInverseS,TempSum);
  vars.dP[jMax-1] = holder[0];
  vars.dr[jMax-1] = holder[1];
  vars.dL[jMax-1] = holder[2];
  vars.dT[jMax-1] = holder[3];

  // for (int i=0; i<iMax; i++)
  //   {

  //    vars.dx[i][jMax-1]= holder[i];
  //    ratio[i][jMax-1] = vars.dx[i][jMax-1]/vars.x[i][jMax-1];

  //   }


  /*
    Now, work backwards from j=jMax-2 to j=0,
    solving for all of the dx[i][j]'s.
   */

  double foo;
  for (int j=jMax-2; j>=0; j--)
    {
      TempB = B[j];
      // i = 0
      vars.dP[j] = A[j][0] + (B[j][0][0] * vars.dP[j+1]) + (B[j][0][1] * vars.dr[j+1]) + (B[j][0][2] * vars.dL[j+1]) + (B[j][0][3] * vars.dT[j+1]);
      // i = 1
      vars.dr[j] = A[j][1] + (B[j][1][0] * vars.dP[j+1]) + (B[j][1][1] * vars.dr[j+1]) + (B[j][1][2] * vars.dL[j+1]) + (B[j][1][3] * vars.dT[j+1]);
      // i = 2
      vars.dL[j] = A[j][2] + (B[j][2][0] * vars.dP[j+1]) + (B[j][2][1] * vars.dr[j+1]) + (B[j][2][2] * vars.dL[j+1]) + (B[j][2][3] * vars.dT[j+1]);
      // i = 3
      vars.dT[j] = A[j][3] + (B[j][3][0] * vars.dP[j+1]) + (B[j][3][1] * vars.dr[j+1]) + (B[j][3][2] * vars.dL[j+1]) + (B[j][3][3] * vars.dT[j+1]);

      // for (int i=0; i<iMax; i++)
      // 	{
      // 	  foo = 0;
	  
      // 	  for (int k=0; k<iMax; k++)
      // 	    {
      // 	      TempB[i][k] = B[i][k][j];	      
      // 	      foo += B[i][k][j] * vars.dx[k][j+1];

      // 	    }


      // 	  vars.dx[i][j] = A[i][j] + foo;
      // 	  ratio[i][j] = vars.dx[i][j]/vars.x[i][j];
    
      // 	}
    
    }


}
