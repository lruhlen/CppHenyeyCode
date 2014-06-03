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
#include "matrixDivide.h"
#include "convert_to_vec2d.h"
#include "convert_from_vec2d.h"
#include "FindMax.h"
#include <float.h>

vec2d MakeHenyeyMatrix(vec3d &C, vec3d &D, vec3d &E)
{
   // vec2d HenyeyMatrix(jMax,jMax);
//  for (int j=0; j<jMax; j+=4)
//    {
//      for (int row = j; row < j+4; row++)
//	{
//	  for (int col = j+(j%4); col < j+4; col++)
//	    {
//	      HenyeyMatrix[row][col] = D[row%4][col%4][j];
//
//	      if (row >= 4)
//		{
//		  HenyeyMatrix[row][col-4] = C[row%4][col%4][j];
//		}
//
//	      if (row < jMax-4)
//		{
//		  HenyeyMatrix[row][col+4] = E[row%4][col%4][j];
//		}
//
//	    } 
//	}
//    }
//

  int size = jMax*4;
  vec2d HenyeyMatrix(size,size);
  // vec3d TestC(iMax,iMax,jMax,1), TestD(iMax,iMax,jMax,2), TestE(iMax,iMax,jMax,3);
  
  
  for (int j=0; j<size; j+=4)
    {
      for (int row = j; row < j+4; row++)
	{ //cout<<endl;
	  for (int col = j+(j%4); col < j+4; col++)
	    {
	     
	      HenyeyMatrix[row][col] = D[row%4][col%4][j/4];
	      //cout<<"Filling in D[i="<<row%4<<"][k="<<col%4<<"][j="<<j/4<<"]\n";

	      if (row >= 4)
		{
		  HenyeyMatrix[row][col-4] = C[row%4][col%4][j/4];
		  //	  cout<<"Filling in C[i="<<row%4<<"][k="<<col%4<<"][j="<<j/4<<"]\n";

		}

	      if (row < size-4)
		{
		  HenyeyMatrix[row][col+4] = E[row%4][col%4][j/4];
		  //	  cout<<"Filling in E[i="<<row%4<<"][k="<<col%4<<"][j="<<j/4<<"]\n";

		}

	    } 
	}
    }



  return HenyeyMatrix;
}
