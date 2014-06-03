#include <iostream>
#include <vector>
#include <math.h>
#include "global.h"
using namespace std;



double FindMax(struct vec3d &matrix)
{
  double max = matrix[0][0][0];
  int NumSlices = matrix.size();
  int NumRows = matrix[0].size();
  int NumCols = matrix[0][0].size();

  for(int slice =0; slice<NumSlices; slice++)
    {
      for(int row = 0; row < NumRows; row++)
	{
	  for (int col=0; col < NumCols; col++)
	    {
	      if (fabs(max) < fabs(matrix[slice][row][col]))
		{
		  max = matrix[slice][row][col];
		}
	    }      
	}
    }
  return max;
}





double FindMax(struct vec2d &matrix)
{
  double max = matrix[0][0];
  int NumRows = matrix.size();
  int NumCols = matrix[0].size();

  for(int row = 0; row < NumRows; row++)
    {
      for (int col=0; col < NumCols; col++)
	{
	  if (fabs(max) < fabs(matrix[row][col]))
	    {
	      max = matrix[row][col];

	    }
	}      
    }

  return max;
}



double FindMax(vector<vector<double> > &matrix)
{
  double max = matrix[0][0];
  int NumRows = matrix.size();
  int NumCols = matrix[0].size();

  for(int row = 0; row < NumRows; row++)
    {
      for (int col=0; col < NumCols; col++)
	{
	  if (fabs(max) < fabs(matrix[row][col]))
	    {
	      max = matrix[row][col];
	    }
	}      
    }
  
  return max;
}




double FindMax(vector<double>  &matrix)
{
  double max = matrix[0];
  int NumCols = matrix.size();

      for (int col=0; col < NumCols; col++)
	{
	  if (fabs(max) < fabs(matrix[col]))
	    {
	      max = matrix[col];
	    }
	     
    }
  
  return max;
}

