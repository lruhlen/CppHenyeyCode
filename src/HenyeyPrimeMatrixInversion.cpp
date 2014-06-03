#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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
#include "PartialDeriv.h"
#include <float.h>
#include "matrixInvert.h"
#include "cleanMatrix.h"
#include "matrixExtract.h"
#include "matrixImplant.h"
#include "flattenMatrix.h"
#include "unflattenMatrix.h"
#include "pause_for_user.h"
#include "printMatrixToFile.h"
using namespace std;


void HenyeyPrimeMatrixInversion(struct bundle &vars, vec3d bigCprime, vec3d bigDprime, vec3d bigEprime, vec2d bigGprime)
{
  vec2d bigAprime(iMax,jMax,0);
  vec3d bigBprime(iMax,iMax,jMax,0);
  
  vec2d S(iMax,iMax,0), InverseS(iMax,iMax,0), Cprime(iMax,iMax,0);
  
  OneD dx(iMax), temp2(iMax);
  vec2d temp1(iMax,iMax);

  FILE * outfile;
  outfile = fopen("/home/grads/laurel/Desktop/PlanetsResearch/TestCalcsInMathematica/ABCDEGS_matrices_from_the_code.txt","w");

  //-----------------------------------------------------------
  // Calculate the A and B matrices at j=0
  //-----------------------------------------------------------
 
  int j=0;

  vec2d Dprime = matrixExtract(bigDprime,j);
  vec2d InverseDprime = matrixInvert(Dprime);

  OneD Gprime = matrixExtract(bigGprime,j);

  OneD Aprime = matrixMultiply(InverseDprime,Gprime);
  Aprime = matrixMultiply(-1.0,Aprime);

  vec2d Eprime = matrixExtract(bigEprime,j);
  vec2d Bprime = matrixMultiply(InverseDprime,Eprime);
  Bprime = matrixMultiply(-1.0,Bprime);
  matrixImplant(Bprime,bigBprime,j);


  fprintf(outfile,"\nj=%i\n",j);
  fprintf(outfile,"\nAprime:\n"); printMatrixToFile(outfile,Aprime);
  fprintf(outfile,"\nBprime:\n"); printMatrixToFile(outfile,Bprime);
  fprintf(outfile,"\nCprime:\n"); printMatrixToFile(outfile,Cprime);
  fprintf(outfile,"\nDprime:\n"); printMatrixToFile(outfile,Dprime);
  fprintf(outfile,"\nInverseDprime:\n"); printMatrixToFile(outfile,InverseDprime);  
  fprintf(outfile,"\nEprime:\n"); printMatrixToFile(outfile,Eprime);



  //-----------------------------------------------------------
  // Forward-bootstrap the A and B values from j=1 to j=jMax-1
  //-----------------------------------------------------------
  
  for (j=1; j<jMax; j++)
    {
      // Extract necessary values from their respective home matrices
      Cprime = matrixExtract(bigCprime,j);
      Dprime = matrixExtract(bigDprime,j);
      Gprime = matrixExtract(bigGprime,j);
      Eprime = matrixExtract(bigEprime,j);

      // Calculate S and S^-1
      S = matrixMultiply(Cprime,Bprime);
      S = addMatrix(S,Dprime);
      InverseS = matrixInvert(S); 

      // Calculate the new Aprime value
      Aprime = matrixMultiply(Cprime,Aprime);
      Aprime = addMatrix(Gprime,Aprime);
      Aprime = matrixMultiply(InverseS,Aprime);
      Aprime = matrixMultiply(-1.0,Aprime);
 
      // Calculate the new Bprime value
      Bprime = matrixMultiply(InverseS,Eprime);
      Bprime = matrixMultiply(-1.0,Bprime);

      // Implant the new values into their respective home matrices
      matrixImplant(Aprime,bigAprime,j);
      matrixImplant(Bprime,bigBprime,j);

      fprintf(outfile,"\nj=%i\n",j);
      fprintf(outfile,"\nAprime:\n"); printMatrixToFile(outfile,Aprime);
      fprintf(outfile,"\nBprime:\n"); printMatrixToFile(outfile,Bprime);
      fprintf(outfile,"\nCprime:\n"); printMatrixToFile(outfile,Cprime);
      fprintf(outfile,"\nDprime:\n"); printMatrixToFile(outfile,Dprime);
      fprintf(outfile,"\nEprime:\n"); printMatrixToFile(outfile,Eprime);
      fprintf(outfile,"\nS:\n"); printMatrixToFile(outfile,S);
      fprintf(outfile,"\nInverseS:\n"); printMatrixToFile(outfile,InverseS);
      

    }



  //-----------------------------------------------------------
  //  Solve for the dxprime[i][j=surface] values
  //-----------------------------------------------------------
  j = jMax-1;

  Cprime = matrixExtract(bigCprime,j);
  Bprime = matrixExtract(bigBprime,j-1);
  Dprime = matrixExtract(bigDprime,j);

  Gprime = matrixExtract(bigGprime,j);
  Aprime = matrixExtract(bigAprime,j-1);

  temp1 = matrixMultiply(Cprime,Bprime);
  temp1 = addMatrix(Dprime,temp1);
  temp1 = matrixInvert(temp1);
  temp1 = matrixMultiply(-1.0,temp1);

  temp2 = matrixMultiply(Cprime,Aprime);
  temp2 = addMatrix(Gprime,temp2);
  
  dx = matrixMultiply(temp1,temp2);
  matrixImplant(dx,vars.dxprime,j);

 
  //-----------------------------------------------------------
  //  Now, work backwards from j=jMax-2 to j=0,
  //  solving for all of the dx[i][j]'s.
  //-----------------------------------------------------------
 
  for (j=jMax-2; j>=0; j--)
    {
      Aprime = matrixExtract(bigAprime,j);
      Bprime = matrixExtract(bigBprime,j);

      dx = matrixMultiply(Bprime,dx);
      dx = addMatrix(Aprime,dx);

      matrixImplant(dx,vars.dxprime,j);
      

    }

  fclose(outfile);

}

  


