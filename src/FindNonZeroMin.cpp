#include <iostream>
#include <vector>
#include <math.h>
#include "global.h"
using namespace std;
const double inf = 1e128;


double FindNonZeroMin(struct vec3d &matrix)
{
  //  double min = matrix[0][0][0];
  double min = inf;
  int NumSlices = matrix.size();
  int NumRows = matrix[0].size();
  int NumCols = matrix[0][0].size();

  for(int slice =0; slice<NumSlices; slice++)
    {
      for(int row = 0; row < NumRows; row++)
	{
	  for (int col=0; col < NumCols; col++)
	    {
	      if ((fabs(min) > fabs(matrix[slice][row][col])) && (matrix[slice][row][col] !=0))
		{
		  min = matrix[slice][row][col];
		}
	    }      
	}
    }

  if (min == inf)
    {
      min = 0;
    }

  return min;
}


double FindNonZeroMin(struct vec2d &matrix)
{
  double min = inf;
  int NumRows = matrix.size();
  int NumCols = matrix[0].size();

  for(int row = 0; row < NumRows; row++)
    {
      for (int col=0; col < NumCols; col++)
	{
	  if ((fabs(min) > fabs(matrix[row][col])) && (matrix[row][col] !=0))
	    {
	      min = matrix[row][col];
	    }
	}      
    }

  if (min == inf)
    {
      min = 0;
    }


  return min;
}

double FindNonZeroMin(vector<vector<double> > &matrix)
{
  double min = inf;
  int NumRows = matrix.size();
  int NumCols = matrix[0].size();

  for(int row = 0; row < NumRows; row++)
    {
      for (int col=0; col < NumCols; col++)
	{
	  if ((fabs(min) > fabs(matrix[row][col])) && (matrix[row][col]!=0))
	    {
	      min = matrix[row][col];
	    }
	}      
    }
 
  if (min == inf)
    {
      min = 0;
    }

  
  return min;
}

double FindNonZeroMin(vector<double>  &matrix)
{
  double min = inf;
  int NumCols = matrix.size();

      for (int col=0; col < NumCols; col++)
	{
	  if ((fabs(min) > fabs(matrix[col])) && (matrix[col] != 0))
	    {
	      min = matrix[col];
	    }
	     
    }
 
  if (min == inf)
    {
      min = 0;
    }

  
  return min;
}
