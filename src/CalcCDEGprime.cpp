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
#include "G1Jprime.h"
#include "G2Jprime.h"
#include "G3Jprime.h"
#include "G4Jprime.h"
#include "cleanMatrix.h"
#include <float.h>
#include "pause_for_user.h"


using namespace std;

void CalcCDEGprime(bundle &vars, vec3d &Cprime, vec3d &Dprime, vec3d &Eprime, vec2d &Gprime)
{
  //+++++++++++++++++++++++++++++++++++++++
  // Calculate the plain old G values first.
  // Use a seperate function for each of 
  // the four G_ij's
  //+++++++++++++++++++++++++++++++++++++++
  
  Gprime[0] = G1Jprime(vars);
  Gprime[1] = G2Jprime(vars);
  Gprime[2] = G3Jprime(vars);
  Gprime[3] = G4Jprime(vars);
  

  // Need to worry about boundary conditions here?...


  /*+++++++++++++++++++++++++++++++++++++++
    Now, make a set of vars that's ever 
    so slightly different from the the 
    regular ones. 
  
    Need to vary each of the 4 x-vars indep-
    ently of the others, and update the
    dependent vars (kappa, rho, etc.) based
    on each of those 4 different sets of
    inputs.
    +++++++++++++++++++++++++++++++++++++++*/

  double max;
  double epsilon = pow(10.0,-8.0);

  // Prepare your variables for the onslaught...
  bundle varied_vars;
  vec3d GplusdG(iMax,iMax,jMax),dG(iMax,iMax,jMax);
  vec2d deltaxprime(iMax,jMax,1), deltax(iMax,jMax), deltaxprimeC(iMax,jMax), deltaxprimeD(iMax,jMax), deltaxprimeE(iMax,jMax), tempG(iMax,jMax);
  bool use_xprime = true;
  bool use_x = false;


  for (int OneToVary=0; OneToVary < iMax; OneToVary++)
    {
      
      varied_vars = vars;

      if (OneToVary == 2) 
	{
	  deltaxprime[OneToVary] = matrixMultiply(epsilon,vars.xprime[OneToVary]);
	  varied_vars.xprime[OneToVary] = matrixMultiply(1.0+epsilon,vars.xprime[OneToVary]);
	}
     else
       { // for the logarithmicly scaled variables:
	 deltaxprime[OneToVary] = matrixMultiply(epsilon,deltaxprime[OneToVary]);
	 varied_vars.xprime[OneToVary] = addMatrix(epsilon,varied_vars.xprime[OneToVary]); 
       }

      varied_vars.update_vars(use_xprime);
  

     for (int shift = -1; shift <=1; shift++)
	{
	  
	  GplusdG[0][OneToVary] = G1Jprime(vars, varied_vars, OneToVary, shift); 
	  GplusdG[1][OneToVary] = G2Jprime(vars, varied_vars, OneToVary, shift); 
	  GplusdG[2][OneToVary] = G3Jprime(vars, varied_vars, OneToVary, shift); 
	  GplusdG[3][OneToVary] = G4Jprime(vars, varied_vars, OneToVary, shift); 


	  tempG = matrixMultiply(-1.0,Gprime); 

	  dG[0][OneToVary] = addMatrix(GplusdG[0][OneToVary],tempG[0]); 
	  dG[1][OneToVary] = addMatrix(GplusdG[1][OneToVary],tempG[1]);
	  dG[2][OneToVary] = addMatrix(GplusdG[2][OneToVary],tempG[2]); 
	  dG[3][OneToVary] = addMatrix(GplusdG[3][OneToVary],tempG[3]);


	  if (shift == -1) 
	    { 
	      deltaxprimeC[OneToVary] = deltaxprime[OneToVary];
	      deltaxprimeC[OneToVary].erase(deltaxprimeC[OneToVary].end()-1); 
	      deltaxprimeC[OneToVary].insert(deltaxprimeC[OneToVary].begin(),1.0);
	       
	      Cprime[0][OneToVary] = matrixDivide(dG[0][OneToVary],deltaxprimeC[OneToVary]);
	      Cprime[1][OneToVary] = matrixDivide(dG[1][OneToVary],deltaxprimeC[OneToVary]); 
	      Cprime[2][OneToVary] = matrixDivide(dG[2][OneToVary],deltaxprimeC[OneToVary]); 
	      Cprime[3][OneToVary] = matrixDivide(dG[3][OneToVary],deltaxprimeC[OneToVary]);
	      
	      
	      Cprime[0][OneToVary][0] = 0.0 ; 
	      Cprime[1][OneToVary][0] = 0.0;
	      Cprime[2][OneToVary][0] = 0.0; 
	      Cprime[3][OneToVary][0] = 0.0;

	    } 
	  else if (shift == 1)
	    { 
	      deltaxprimeE[OneToVary] = deltaxprime[OneToVary];
	      deltaxprimeE[OneToVary].erase(deltaxprimeE[OneToVary].begin()); 
 	      deltaxprimeE[OneToVary].push_back(1.0);
	      
	      Eprime[0][OneToVary] = matrixDivide(dG[0][OneToVary],deltaxprimeE[OneToVary]); 
	      Eprime[1][OneToVary] = matrixDivide(dG[1][OneToVary],deltaxprimeE[OneToVary]);
	      Eprime[2][OneToVary] = matrixDivide(dG[2][OneToVary],deltaxprimeE[OneToVary]); 
	      Eprime[3][OneToVary] = matrixDivide(dG[3][OneToVary],deltaxprimeE[OneToVary]);
	      
	      
	      Eprime[0][OneToVary][jMax-1] = 0.0; 
	      Eprime[1][OneToVary][jMax-1] = 0.0;
	      Eprime[2][OneToVary][jMax-1] = 0.0; 
	      Eprime[3][OneToVary][jMax-1] = 0.0;
	      

	    }
	  else if (shift == 0) 
	    {
	      deltaxprimeD[OneToVary] = deltaxprime[OneToVary]; 
	      Dprime[0][OneToVary] = matrixDivide(dG[0][OneToVary],deltaxprimeD[OneToVary]); 
	      Dprime[1][OneToVary] = matrixDivide(dG[1][OneToVary],deltaxprimeD[OneToVary]); 
	      Dprime[2][OneToVary] = matrixDivide(dG[2][OneToVary],deltaxprimeD[OneToVary]); 
	      Dprime[3][OneToVary] = matrixDivide(dG[3][OneToVary],deltaxprimeD[OneToVary]); 
	    }
    

	} // end of the shift loop
 
    } // end of the OneToVary loop
     
} // Fin!



