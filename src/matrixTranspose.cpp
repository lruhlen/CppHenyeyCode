#include <iostream>
#include <vector>
#include "printMatrix.h"
#include "global.h"
using namespace std;

struct vec2d matrixTranspose(struct vec2d &matrix){
  int rows = matrix.size();
  int cols = matrix[0].size();
  
  struct vec2d result(cols,rows);

  for (int r=0; r<rows; r++)
    { 

      for (int c=0; c<cols; c++)
	{
	  result[c][r] = matrix[r][c];
	}
    }

 return result;

}

////Transposing a multi-dimensional matrix
vector<vector<double> > matrixTranspose(vector< vector<double> > &matrix){
 
  int rows = matrix.size();

  int cols = matrix[0].size();

  vector< vector<double> > result(cols,rows);

  for (int r=0; r<rows; r++)
    { 

      for (int c=0; c<cols; c++)
	{
	  result[c][r] = matrix[r][c];
	}
    }

 return result;
}

/*
///// Transposing a vector (still returns a matrix)
vector<vector<double> > matrixTranspose( vector<double> &matrix){
  
  int cols = matrix.size();
  int rows = 1;
  vector< vector<double> > result(cols,rows);

  for (int r=0; r<rows; r++)
    {
      for (int c=0; c<cols; c++)
	{
	  result[r][c] = matrix[c];
	}
    }

 return result;
}
*/

/*
// Transposing a single column vector to a single row vector
OneD matrixTranspose(vec2d &matrix)
{ 
  int cols = matrix.size();
  int rows = 1;
  
  OneD result(cols);

   for (int r=0; r<rows; r++)
    {
      for (int c=0; c<cols; c++)
	{
	  result[c] = matrix[r][c];
	}
    }

 return result; 
}
*/


// Transposing a single row vector to a single column vector
vec2d matrixTranspose(OneD &matrix)
{

  int rows = matrix.size();
  int cols = 1;


  vec2d result(rows,cols);

  for (int c=0; c<cols; c++)
    {
      for (int r=0; r<rows; r++)
	{
	  result[r][c] = matrix[r];
	}
    }
  
  return result;
}
