#include <vector>
#include <math.h>
#include <string.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "printMatrix.h"
#include "matrixMultiply.h"
#include "addMatrix.h" 
#include <float.h>

using namespace std;

vec3d cleanMatrix(struct vec3d matrix)
{
  vec3d result = matrix;
  int nrows = matrix.size();
  int ncols = matrix[0].size();
  int nbeams = matrix[0][0].size();
  

  for (int row=0; row<nrows; row++)
    {
      for (int col=0; col<ncols; col++)
	{
	  for (int beam = 0; beam < nbeams; beam++)
	    {
	      if (fabs(matrix[row][col][beam])<= (20.0*DBL_EPSILON))
		{
		  result[row][col][beam] = 0;
		}
	    }
	}
      
    }
  return result;
}


vec2d cleanMatrix(struct vec2d matrix)
{
  vec2d result = matrix;
  int nrows = matrix.size();
  int ncols = matrix[0].size();
  
  for (int row=0; row<nrows; row++)
    {
      for (int col=0; col<ncols; col++)
	{
	  if (fabs(matrix[row][col])<= (20.0*DBL_EPSILON))
	    {
	      result[row][col] = 0;
	    }
	}

    }
  
  return result;
}

vector<double> cleanMatrix(vector<double> matrix)
{
  int ncols = matrix.size();
  vector<double> result = matrix;
  
  for (int col=0; col<ncols; col++)
    {
      if (fabs(matrix[col])<= (20.0*DBL_EPSILON))
	{
	  result[col] = 0;
	}
      
      
    }

  return result;

}


double cleanMatrix(double matrix)
{
  double result = matrix;
   if (fabs(matrix)<= (20.0*DBL_EPSILON))
	{
	  result = 0;
	}
   
   return result;
}
