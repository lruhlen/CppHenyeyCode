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
#include "subtractMatrix.h"
#include "matrixMultiply.h"
#include "matrixDivide.h"
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
#include "fourbyfourinvert.h"
#include "ReadInArray.h"
#include "FindNonZeroMax.h"

using namespace std;

extern string filePath, versionNum;
extern bool WriteOutput;

void modifiedHenyeyMatrixInversion(struct bundle &vars, vec3d &C, vec3d &D, vec3d &E, vec2d &G, string iterNum)
{

  vec2d A(jMax,iMax);
  vec2d Sum(jMax,iMax);  
  vec3d S(jMax,iMax,iMax), B(jMax,iMax,iMax), InverseS(jMax,iMax,iMax); 
  OneD tempJ(4), tempJminus(4);

  //  vec3d PeterS(jMax,iMax,iMax) , PeterInverseS(jMax,iMax,iMax) ;
  //  PeterS = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/n32_1Msun_Smatrices.txt",jMax,iMax,iMax);
  //  PeterInverseS = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/n32_1Msun_inverseSmatrices.txt",jMax,iMax,iMax);
  //  vec2d PeterSum(jMax,iMax);
  //  PeterSum = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/n32_1Msun_Sum_values.txt",jMax,iMax);
  //  vec3d tempS(jMax,iMax,iMax,0), tempAvg(jMax,iMax,iMax,0);


  //-----------------------------------------------------------
  // Forward-bootstrap the A and B values from j=0 to j=jMax-1
  //-----------------------------------------------------------
  for (int j=0; j<jMax; j++)
    {
      // Start with the j=0 special case
       if (j==0)
       	{
	  S[j] = D[j];
	  Sum[j] = G[j];
       	}
       else 
       	{
	  S[j] = matrixMultiply(C[j],B[j-1]);
	  S[j] = addMatrix(S[j],D[j]);
        
	  Sum[j] = matrixMultiply(C[j],A[j-1]);
	  Sum[j] = addMatrix(G[j],Sum[j]);	  
       	}	  	  	  

       //       if (j < jMax-2)
       // 	 {
       InverseS[j] = fourbyfourinvert(S[j]);		   
        	   // InverseS[j] = matrixInvert(S[j]);
        // 	 }
        // else
        // 	 {
	// 	   InverseS[j] = PeterInverseS[j];
	// 	   Sum[j] = matrixMultiply(-1.0,PeterSum[j]);
        // 	 }

       //       InverseS[j] = fourbyfourinvert(S[j]);

       //       Sum[j] = matrixMultiply(-1.0,PeterSum[j]);
       A[j] = matrixMultiply(InverseS[j],Sum[j]);
       A[j] = matrixMultiply(-1.0,A[j]);
       B[j] = matrixMultiply(InverseS[j],E[j]);
       B[j] = matrixMultiply(-1.0,B[j]);     
       
    }
  cout<<"\t\tDone calculating the As and Bs\n";

  if (WriteOutput)
    {
      ofstream Aout, Bout, Sout, invSout, Sumout;

      string tempName = filePath + "_A_debug_v" + versionNum + "_iter_" +iterNum + ".txt";
      Aout.open(tempName.c_str());

      tempName = filePath + "_B_debug_v" + versionNum +  "_iter_" + iterNum +".txt";
      Bout.open(tempName.c_str());

      tempName = filePath + "_S_debug_v" + versionNum +  "_iter_" + iterNum +".txt";
      Sout.open(tempName.c_str());

      tempName = filePath + "_invS_debug_v" + versionNum +  "_iter_" + iterNum +".txt";
      invSout.open(tempName.c_str());

      tempName = filePath + "_Sum_debug_v" + versionNum +  "_iter_" + iterNum +".txt";
      Sumout.open(tempName.c_str());

      
      for (int j=0; j<jMax; j++)
	{
	  for(int i=0; i<iMax; i++)
	    {
	      Aout<<A[j][i]<<"\t";
	      Sumout<<Sum[j][i]<<"\t";

	      for (int k=0; k<iMax; k++)
		{
		  invSout<<InverseS[j][i][k]<<"\t";
		  Sout<<S[j][i][k]<<"\t";
		  Bout<<B[j][i][k]<<"\t";
		}
	    }
	  Aout<<endl;
	  Bout<<endl;
	  Sout<<endl;
	  invSout<<endl;
	  Sumout<<endl;
	}

      Aout.close();
      Bout.close();
      Sout.close();
      invSout.close();
      Sumout.close();
    }

  cout<<"\t\tStarting the dX backsolving\n";
  /*
    Solve for the dx surface values
  */ 
  // vars.dP[jMax-1] = A[jMax-1][0];
  // vars.dr[jMax-1] = A[jMax-1][1];
  // vars.dL[jMax-1] = A[jMax-1][2];
  // vars.dT[jMax-1] = A[jMax-1][3];

  tempJ[0] = A[jMax-1][0];
  tempJ[1] = A[jMax-1][1];
  tempJ[2] = A[jMax-1][2];
  tempJ[3] = A[jMax-1][3];

  vars.dP[jMax-1] = tempJ[0];
  vars.dr[jMax-1] = tempJ[1];
  vars.dL[jMax-1] = tempJ[2];
  vars.dT[jMax-1] = tempJ[3];

  /*
    Now, work backwards from j=jMax-2 to j=0,
    solving for all of the dx[i][j]'s.
  */
  for (int j=jMax-1; j>0; j--)
    {
      tempJminus = matrixMultiply(B[j-1],tempJ);
      tempJminus = addMatrix(A[j-1],tempJminus);
      
      vars.dP[j-1] = tempJminus[0];
      vars.dr[j-1] = tempJminus[1];
      vars.dL[j-1] = tempJminus[2];
      vars.dT[j-1] = tempJminus[3];

      tempJ = tempJminus;
    }

  
}
