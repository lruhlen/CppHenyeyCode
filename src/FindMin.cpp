#include <iostream>
#include <vector>
#include <math.h>
#include "global.h"
using namespace std;



double FindMin(struct vec3d &matrix)
{
  double min = matrix[0][0][0];
  int NumSlices = matrix.size();
  int NumRows = matrix[0].size();
  int NumCols = matrix[0][0].size();

  for(int slice =0; slice<NumSlices; slice++)
    {
      for(int row = 0; row < NumRows; row++)
	{
	  for (int col=0; col < NumCols; col++)
	    {
	      if (fabs(min) > fabs(matrix[slice][row][col]))
		{
		  min = matrix[slice][row][col];
		}
	    }      
	}
    }
  return min;
}


double FindMin(struct vec2d &matrix)
{
  double min = matrix[0][0];
  int NumRows = matrix.size();
  int NumCols = matrix[0].size();

  for(int row = 0; row < NumRows; row++)
    {
      for (int col=0; col < NumCols; col++)
	{
	  if (fabs(min) > fabs(matrix[row][col]))
	    {
	      min = matrix[row][col];
	    }
	}      
    }
  
  return min;
}

double FindMin(vector<vector<double> > &matrix)
{
  double min = matrix[0][0];
  int NumRows = matrix.size();
  int NumCols = matrix[0].size();

  for(int row = 0; row < NumRows; row++)
    {
      for (int col=0; col < NumCols; col++)
	{
	  if (fabs(min) > fabs(matrix[row][col]))
	    {
	      min = matrix[row][col];
	    }
	}      
    }
  
  return min;
}

double FindMin(vector<double>  &matrix)
{
  double min = matrix[0];
  int NumCols = matrix.size();

      for (int col=0; col < NumCols; col++)
	{
	  if (fabs(min) > fabs(matrix[col]))
	    {
	      min = matrix[col];
	    }
	     
    }
  
  return min;
}
