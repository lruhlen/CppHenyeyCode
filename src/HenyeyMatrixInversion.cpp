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


void HenyeyMatrixInversion(struct bundle &vars, vec3d C, vec3d D, vec3d E, vec2d G)
{
  int moose;

  vec2d TempG(iMax,1), TempA(iMax,1), TempSum(iMax,1), Tempdx(iMax,1);
  vec2d A(iMax,jMax), TempB(iMax,iMax,0), TempC(iMax,iMax,0), TempD(iMax,iMax,0), TempE(iMax,iMax,0);
  vec2d TempInverseS(iMax,iMax,0), TempS(iMax,iMax,0), Sum(iMax,jMax);

  vec2d ratio(iMax,jMax);

  vec3d S(iMax,iMax,jMax), B(iMax,iMax,jMax), InverseS(iMax,iMax,jMax); 

  string continueHit;

  //-----------------------------------------------------------
  // Forward-bootstrap the A and B values from j=0 to j=jMax-1
  //-----------------------------------------------------------
  for (int j=0; j<jMax; j++)
    {
 
      // Fill the Temp variables, one block at a time
      for (int i=0; i<iMax; i++)
	{
	  TempG[i][0] = G[i][j];
	  
	  for (int k=0; k<iMax; k++)
	    {
	      TempC[i][k] = C[i][k][j];
	      TempD[i][k] = D[i][k][j];
	      TempE[i][k] = E[i][k][j];

	    }

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
	      vec2d bar = matrixMultiply(TempC,TempA);
	      TempSum = addMatrix(TempG,bar);
	      
	    }



	  /*
	    Here, TempA and TempB are updated to reflect
	    their values at the _current_ j index.	    
	   */
	  TempA = matrixMultiply(TempInverseS,TempSum);
	  TempB = matrixMultiply(TempInverseS,TempE);

	}
      
  

      // Insert the Temp A, B, and S values into their full array counterparts 
      for (int i=0; i<iMax; i++)
	{
	  A[i][j] = TempA[i][0];
	  Sum[i][j] = TempSum[i][0];

	  for (int k=0; k<iMax; k++)
	    {
	      B[i][k][j] = TempB[i][k];
	      S[i][k][j] = TempS[i][k];
	      InverseS[i][k][j] = TempInverseS[i][k];

	    }
	}
    }
  


  /*
    Solve for the dx[i][j=surface] values
  */
  vec2d holder = matrixMultiply(TempInverseS,TempSum);

  for (int i=0; i<iMax; i++)
    {

     vars.dx[i][jMax-1]= holder[i][0];
     ratio[i][jMax-1] = vars.dx[i][jMax-1]/vars.x[i][jMax-1];

    }


  /*
    Now, work backwards from j=jMax-2 to j=0,
    solving for all of the dx[i][j]'s.
   */

  double foo;
  for (int j=jMax-2; j>=0; j--)
    {
      for (int i=0; i<iMax; i++)
	{
	  foo = 0;
	  
	  for (int k=0; k<iMax; k++)
	    {
	      TempB[i][k] = B[i][k][j];
	      
	      foo += B[i][k][j] * vars.dx[k][j+1];
	    }

	  if (debugflag >=3)
	    {
	      cout<<"B*dx[j+1] = "<<foo<<endl;
	      cout<<"A[i][j] = "<<A[i][j]<<endl;
	    }

	  vars.dx[i][j] = A[i][j] + foo;
	  ratio[i][j] = vars.dx[i][j]/vars.x[i][j];
    
	}
    
    }


}
