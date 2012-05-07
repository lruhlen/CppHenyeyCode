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

void CalcCDEG(bundle &vars, vec3d &C, vec3d &D, vec3d &E, vec2d &G)
{
  //+++++++++++++++++++++++++++++++++++++++
  // Calculate the plain old G values first.
  // Use a seperate function for each of 
  // the four G_ij's
  //+++++++++++++++++++++++++++++++++++++++
  
  G[0] = G1J(vars);
  G[1] = G2J(vars);
  G[2] = G3J(vars);
  G[3] = G4J(vars);
  
  if (debugflag >= 3 ){ 
    double maxG;
    cout<<"\t\t Printing the G_i results:\n";
    
    maxG = FindMax(G[0]);
    cout<<"\n \t\t max(G[0]): "<<maxG<<"\n";
    //  	  printMatrix(G[0]);
    
    maxG = FindMax(G[1]);
    cout<<"\n \t \t max(G[1])): "<<maxG<<"\n";
    //  	  printMatrix(G[1]);
    maxG = FindMax(G[2]);
    cout<<"\n \t\t max(G[2])): "<<maxG<<"\n";
    //  	  printMatrix(G[2]);
    maxG = FindMax(G[3]);
    cout<<"\n \t\t max(G[3])): "<<maxG<<"\n";
    //  	  printMatrix(G[3]);
  }
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
  
  // Prepare your variables for the onslaught...
  bundle varied_vars;
  vec3d GplusdG(iMax,iMax,jMax),dG(iMax,iMax,jMax);
  vec2d deltax(iMax,jMax), deltaxC(iMax,jMax), deltaxD(iMax,jMax), deltaxE(iMax,jMax), tempG(iMax,jMax);

  for (int OneToVary=0; OneToVary < iMax; OneToVary++)
    {
      deltax[OneToVary] = matrixMultiply(0.00000001,vars.x[OneToVary]);
      varied_vars = vars;  
      varied_vars.x[OneToVary] = addMatrix(vars.x[OneToVary],deltax[OneToVary]);
      varied_vars.update_vars(false);
     

      for (int shift = -1; shift <=1; shift++)
	{
	  
	  GplusdG[0][OneToVary] = G1J(vars, varied_vars, OneToVary, shift);
	  GplusdG[1][OneToVary] = G2J(vars, varied_vars, OneToVary, shift);
	  GplusdG[2][OneToVary] = G3J(vars, varied_vars, OneToVary, shift);
	  GplusdG[3][OneToVary] = G4J(vars, varied_vars, OneToVary, shift);


	  tempG = matrixMultiply(-1.0,G);
	  dG[0][OneToVary] = addMatrix(GplusdG[0][OneToVary],tempG[0]);
	  dG[1][OneToVary] = addMatrix(GplusdG[1][OneToVary],tempG[1]);
	  dG[2][OneToVary] = addMatrix(GplusdG[2][OneToVary],tempG[2]);
	  dG[3][OneToVary] = addMatrix(GplusdG[3][OneToVary],tempG[3]);
	  
	  if (shift == -1)
	    {
	      deltaxC[OneToVary] = deltax[OneToVary];
	      deltaxC[OneToVary].erase(deltaxC[OneToVary].end()-1);
	      deltaxC[OneToVary].insert(deltaxC[OneToVary].begin(),1.0);
	      
	      C[0][OneToVary] = matrixDivide(dG[0][OneToVary],deltaxC[OneToVary]);
	      C[1][OneToVary] = matrixDivide(dG[1][OneToVary],deltaxC[OneToVary]);
	      C[2][OneToVary] = matrixDivide(dG[2][OneToVary],deltaxC[OneToVary]);
	      C[3][OneToVary] = matrixDivide(dG[3][OneToVary],deltaxC[OneToVary]);
	      
	      
	      C[0][OneToVary][0] = 0.0 ;
	      C[1][OneToVary][0] = 0.0;
	      C[2][OneToVary][0] = 0.0;
	      C[3][OneToVary][0] = 0.0;

	      if (debugflag >=4)
		{
		  cout<<"G[0][1] = "<<G[0][1]<<endl;
		  cout<<"GplusdG[0]["<<OneToVary<<"][1] = "<<GplusdG[0][OneToVary][1]<<endl;
		}
	      


	      if (debugflag >=4)
		{
		  cout<<"\ndG values for the C[*]["<<OneToVary <<"] calcs:\n";
		  printMatrix(dG[0][OneToVary]); cout<<endl;
		  printMatrix(dG[1][OneToVary]); cout<<endl;
		  printMatrix(dG[2][OneToVary]); cout<<endl;
		  printMatrix(dG[3][OneToVary]); cout<<endl;
		}

	    }
	  else if (shift == 1)
	    {
	      deltaxE[OneToVary] = deltax[OneToVary];
	      deltaxE[OneToVary].erase(deltaxE[OneToVary].begin());
	      deltaxE[OneToVary].push_back(1.0);
	      
	      E[0][OneToVary] = matrixDivide(dG[0][OneToVary],deltaxE[OneToVary]);
	      E[1][OneToVary] = matrixDivide(dG[1][OneToVary],deltaxE[OneToVary]);
	      E[2][OneToVary] = matrixDivide(dG[2][OneToVary],deltaxE[OneToVary]);
	      E[3][OneToVary] = matrixDivide(dG[3][OneToVary],deltaxE[OneToVary]);
	      
	      
	      E[0][OneToVary][jMax-1] = 0.0;
	      E[1][OneToVary][jMax-1] = 0.0;
	      E[2][OneToVary][jMax-1] = 0.0;
	      E[3][OneToVary][jMax-1] = 0.0;
	      

	    }
	  else if (shift == 0)
	    {
	      deltaxD[OneToVary] = deltax[OneToVary];

	      D[0][OneToVary] = matrixDivide(dG[0][OneToVary],deltaxD[OneToVary]);
	      D[1][OneToVary] = matrixDivide(dG[1][OneToVary],deltaxD[OneToVary]);
	      D[2][OneToVary] = matrixDivide(dG[2][OneToVary],deltaxD[OneToVary]);
	      D[3][OneToVary] = matrixDivide(dG[3][OneToVary],deltaxD[OneToVary]);

	    }

	  
	  if (debugflag >=3)
	    {
	      
	      if ((shift == -1) && (OneToVary >= 0)) 
		{
		  cout<<"deltaxC["<<OneToVary<<"] = ";
		  printMatrix(deltaxC[OneToVary]);
		  cout<<endl<<endl;
		}
	      
	      if ((shift == 0) && (OneToVary >= 0)) 
		{
		  cout<<"deltaxD["<<OneToVary<<"] = ";
		  printMatrix(deltaxD[OneToVary]);
		  cout<<endl<<endl;
		}

	      if ((shift == 1) && (OneToVary >= 0)) 
		{
		  cout<<"deltaxE["<<OneToVary<<"] = ";
		  printMatrix(deltaxE[OneToVary]);
		  cout<<endl<<endl;
		}
	    }
	 

     
	}
    }
  
//   int a,b;
//   cout<<"This is the C matrix CalcCDEG is returning:\n";
//   printMatrix(C); cout<<endl;
// 
//  cout<<"Enter G index: ";
//  cin>>a;
//  cout<<"Enter dx index: ";
//  cin>>b;
//  vector<double> ratio = matrixDivide(dG[a][b],G[a]);
//  printMatrix(G[a]);
//
//  printMatrix(dG[a][b]);
//  cout<<endl;
//  printMatrix(deltax[b]);
//  cout<<endl;

  

  
} // Fin!





//     GplusdG[0][OneToVary] = G1J(varied_vars);   
//     GplusdG[1][OneToVary] = G2J(varied_vars);
//     GplusdG[2][OneToVary] = G3J(varied_vars);
//     GplusdG[3][OneToVary] = G4J(varied_vars);
//      
//      deltaxE[OneToVary] = deltax[OneToVary];
//      deltaxC[OneToVary] = deltax[OneToVary];
//
//      deltaxE[OneToVary].erase(deltaxE[OneToVary].begin());
//      deltaxE[OneToVary].push_back(1.0);
//
//      deltaxC[OneToVary].erase(deltaxC[OneToVary].end()-1);
//      deltaxC[OneToVary].insert(deltaxC[OneToVary].begin(),1.0);


  /*+++++++++++++++++++++++++++++++++++++++
    Now combine the raw materials (numerators
    and denominators) into the C, D, and E
    derivatives/values.
    +++++++++++++++++++++++++++++++++++++++*/
 
  // Start with the D's, since they don't involve
  // any array shifting in the denominators...
   
//  for (int i=0; i<iMax; i++)
//    {
//
//      for (int k=0; k<iMax; k++)
//	{
//
//	  // Err, I _think_ this gets you what you want?...
//	  C[i][k]= matrixDivide(dG[i][k],deltaxC[k]);
//	  D[i][k]= matrixDivide(dG[i][k],deltax[k]); 
//	  E[i][k]= matrixDivide(dG[i][k],deltaxE[k]);
//      
//
// 	  C[i][k][0] = 0.0;
//	  E[i][k][jMax-1] = 0.0;
//	}
//
//    }
//
  
