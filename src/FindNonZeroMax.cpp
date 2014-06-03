#include <iostream>
#include <vector>
#include <math.h>
#include "global.h"
using namespace std;



double FindNonZeroMax(struct vec3d &matrix)
{
  double max = 0;
  int NumSlices = matrix.size();
  int NumRows = matrix[0].size();
  int NumCols = matrix[0][0].size();

  for(int slice =0; slice<NumSlices; slice++)
    {
      for(int row = 0; row < NumRows; row++)
	{
	  for (int col=0; col < NumCols; col++)
	    {
	      if ((fabs(max) < fabs(matrix[slice][row][col]))&&(matrix[slice][row][col] !=0))
		{
		  max = matrix[slice][row][col];
		}
	    }      
	}
    }
  return max;
}


double FindNonZeroMax(struct vec2d &matrix)
{
  double max = 0;
  int NumRows = matrix.size();
  int NumCols = matrix[0].size();

  for(int row = 0; row < NumRows; row++)
    {
      for (int col=0; col < NumCols; col++)
	{
	  if ((fabs(max) < fabs(matrix[row][col])) && (matrix[row][col]!=0))
	    {
	      max = matrix[row][col];
	    }
	}      
    }
  
  return max;
}

double FindNonZeroMax(vector<vector<double> > &matrix)
{
  double max = 0;
  int NumRows = matrix.size();
  int NumCols = matrix[0].size();

  for(int row = 0; row < NumRows; row++)
    {
      for (int col=0; col < NumCols; col++)
	{
	  if ((fabs(max) < fabs(matrix[row][col])) && (matrix[row][col]!=0))
	    {
	      max = matrix[row][col];
	    }
	}      
    }
  
  return max;
}

double FindNonZeroMax(vector<double>  &matrix)
{
  double max = 0;
  int NumCols = matrix.size();

      for (int col=0; col < NumCols; col++)
	{
	  if ((fabs(max) < fabs(matrix[col])) && (matrix[col] !=0) )
	    {
	      max = matrix[col];
	    }
	     
    }
  
  return max;
}
