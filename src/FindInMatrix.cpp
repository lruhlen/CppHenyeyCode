#include <iostream>
#include <vector>
#include <math.h>
#include "global.h"
using namespace std;

vector<vector<int> > FindInMatrix(double val, vec3d &matrix)
{
  vector<vector<int> > result;
  vector<int> temp(3,0);

  int NumSlices = matrix.size();
  int NumRows = matrix[0].size();
  int NumCols = matrix[0][0].size();

  for(int slice =0; slice<NumSlices; slice++)
    {
      for(int row = 0; row < NumRows; row++)
	{
	  for (int col=0; col < NumCols; col++)
	    {
	      if (matrix[slice][row][col] == val)
		{
		  temp[0]= slice;
		  temp[1] = row;
		  temp[2] = col;
		  result.push_back(temp);
		}
	    }      
	}
    }

  return result;
}

vector<vector<int> > FindInMatrix(double val, vec2d &matrix)
{
  vector<vector<int> > result;
  vector<int> temp(2,0);

  int NumRows = matrix.size();
  int NumCols = matrix[0].size();

      for(int row = 0; row < NumRows; row++)
	{
	  for (int col=0; col < NumCols; col++)
	    {
	      if (matrix[row][col] == val)
		{
		  temp[0] = row;
		  temp[1] = col;
		  result.push_back(temp);
		}
	    }      
	}
    

  return result;
}


vector<vector<int> > FindInMatrix(double val, vector<double> &matrix)
{
  vector<vector<int> > result;
  vector<int> temp(1,0);

  int NumRows = matrix.size();
 
      for(int row = 0; row < NumRows; row++)
	{
	      if (matrix[row] == val)
		{
		  temp[0] = row;
		  result.push_back(temp);
		}
	          
	}
    

  return result;
}
