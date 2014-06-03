#include <vector>
#include <math.h>
#include <string.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "printMatrix.h"
#include "matrixMultiply.h"
#include "matrixDivide.h"
#include "cleanMatrix.h"
#include "addMatrix.h" 
#include "FindNonZeroMin.h"
#include "FindNonZeroMax.h"
#include <float.h>

using namespace std;

vec2d matrixInvert(vec2d input)
{
  string continueHit;
  vec2d left = input;
  int num = left.size();
  vec2d right(num,num,0);
  vector<double> temprow_left(num,0), temprow_right(num,0);
  double max, pivinv, scale;
  int max_index = 0;
  double overallMin = FindNonZeroMin(left);


  // Set up the 'right hand side' identity matrix
  // This will become the inverse to 'left', and 
  // will be the return value.
  for(int i = 0; i<num; i++) 
    {
      right[i][i] = 1.0;
    }

  // Order the rows of the 'left hand side' matrix
  // in decreasing order of the pivot-point 
  // (absolute) values.
  //
  // Perform the same scaling and swapping operations
  // simultaneously on both 'left' and 'right'.
  for (int col=0; col<num; col++)
    {
      max = 0.0;
      max_index = col;
      // max_index = 0;

      for (int row=col; row<num; row++)
	{

	  if ((fabs(left[row][col]) > fabs(max)) && (left[row][col]!=0.0))
	    {
	      max = left[row][col];
	      max_index = row;
	    }
	}
      
      // Make all of the pivot points equal to one
      left[max_index] = matrixDivide(max,left[max_index]);
      right[max_index] = matrixDivide(max,right[max_index]);


      // Put the row in its proper place
      swap(left[col],left[max_index]);
      swap(right[col],right[max_index]);

      // ...and use it to eliminate elements in the row beneath it
      for (int backrow=num-1; backrow > col; backrow--)
       {      

	  if (left[backrow][col]!= 0)
	    {


	      scale = -1.0 * left[backrow][col];

	      temprow_left = matrixMultiply(scale,left[col]);
	      temprow_right = matrixMultiply(scale,right[col]);
	      
	      left[backrow] = addMatrix(temprow_left,left[backrow]);
	      right[backrow] = addMatrix(temprow_right,right[backrow]);

	    }
	}      
    }


  // At this point, 'left' has been transformed into an upper-triangular matrix.
  // Now, we need to back-solve 'left' to get it into identity form.
  // Again, duplicate all 
  for (int row = num-1; row > 0; row--)
    {
	  
      int col=row;

      for (int elim_row = row-1; elim_row >= 0; elim_row--)
	{
      
	  scale = -1.0 * left[elim_row][col];

	  temprow_left = matrixMultiply(scale,left[row]);
	  temprow_right = matrixMultiply(scale,right[row]);

	  left[elim_row] = addMatrix(temprow_left,left[elim_row]);
	  right[elim_row] = addMatrix(temprow_right,right[elim_row]);
	}
    }
  

  if (debugflag>=5)
    {
      cout<<"===============================================\n";
      cout<<"In matrixInvert: The matrix we started out with:\n";
      printMatrix(input);
      cout<<endl;
      
      
      cout<<"The alleged inverse of this matrix:\n";
      printMatrix(right);
      cout<<endl;
      

      cout<<"Does this look like an identity matrix? IT SHOULD.\n";
      vec2d output = matrixMultiply(input,right);
      printMatrix(output);
      cout<<"===============================================\n";
  
   }


  return right;

}
