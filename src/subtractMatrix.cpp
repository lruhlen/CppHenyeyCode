#include <iostream>
#include <vector>
#include <math.h>
#include "global.h"
#include "printMatrix.h"

using namespace std;

// Subtracting two (struct) tensors
struct vec3d subtractMatrix(struct vec3d &matrixA, struct vec3d &matrixB)
{

  int numSlices = matrixA.size();
  int numRows = matrixA[0].size();
  int numCols = matrixA[0][0].size();
  vec3d result(numSlices,numRows,numCols);
  
  for (int s = 0; s < numSlices; s++)
    {
      for (int r = 0; r < numRows; r++)
	{
	  for (int c = 0; c < numCols; c++) 
	    {
	      result[s][r][c] = matrixA[s][r][c] - matrixB[s][r][c];

	    }
	}
    }

  
  return result;
}

// Subtracting two (struct) matrices
struct vec2d subtractMatrix(struct vec2d &matrixA, struct vec2d &matrixB)
{
  int numRows = matrixA.size();
  int numCols = matrixA[0].size();
  vec2d result(numRows,numCols);
  
    for (int row = 0; row < numRows; row++)
    {
      for (int col = 0; col < numCols; col++) 
	{
	  
	  result[row][col] = matrixA[row][col] - matrixB[row][col];

	}
    }
  return result;
}

// Subtracting a struct matrix to a regular one
struct vec2d subtractMatrix(struct vec2d &matrixA, vector<vector<double> > &matrixB)
{
  int numRows = matrixA.size();
  int numCols = matrixA[0].size();
  vec2d result(numRows,numCols);
  
    for (int row = 0; row < numRows; row++)
    {
      for (int col = 0; col < numCols; col++) 
	{
	  
	  result[row][col] = matrixA[row][col] - matrixB[row][col];

	}
    }
  return result;
}

// Subtracting a struct matrix to a regular one
struct vec2d subtractMatrix( vector<vector<double> > &matrixA, struct vec2d &matrixB)
{
  int numRows = matrixA.size();
  int numCols = matrixA[0].size();
  vec2d result(numRows,numCols);
  
    for (int row = 0; row < numRows; row++)
    {
      for (int col = 0; col < numCols; col++) 
	{
	  
	  result[row][col] = matrixA[row][col] - matrixB[row][col];

	}
    }
  return result;
}


// Subtracting two matrices
vector<vector<double> > subtractMatrix(vector<vector<double> > &matrixA, vector<vector<double> > &matrixB )
{
  int numRows = matrixA.size();
  int numCols = matrixA[0].size();
  vector<vector<double> > result(numRows,numCols);

  for (int row = 0; row < numRows; row++)
    {
      for (int col = 0; col < numCols; col++) 
	{
	  
	  result[row][col] = matrixA[row][col] - matrixB[row][col];

	}
    }
  return result;
}

// Subtracting two vectors
vector<double> subtractMatrix(vector<double> &matrixA, vector<double> &matrixB )
{
  int numElements = matrixA.size();

  vector<double> result(numElements);

  for (int n = 0; n < numElements; n++)
    {  
      result[n] = matrixA[n] + matrixB[n];	
    }
  return result;
}

// Subtracting a constant to all values of a 3d matrix
struct vec3d subtractMatrix(struct vec3d &matrixA, double number)
{
  int numSlices = matrixA.size();
  int numRows = matrixA[0].size();
  int numCols = matrixA[0][0].size();
  vec3d result(numSlices,numRows,numCols);
  
  for (int s = 0; s < numSlices; s++)
    {
      for (int r = 0; r < numRows; r++)
	{
	  for (int c = 0; c < numCols; c++) 
	    {
	      result[s][r][c] = matrixA[s][r][c] - number;

	    }
	}
    }

  
  return result;

}

struct vec3d subtractMatrix(double number, struct vec3d &matrixA)
{
  int numSlices = matrixA.size();
  int numRows = matrixA[0].size();
  int numCols = matrixA[0][0].size();
  vec3d result(numSlices,numRows,numCols);
  
  for (int s = 0; s < numSlices; s++)
    {
      for (int r = 0; r < numRows; r++)
	{
	  for (int c = 0; c < numCols; c++) 
	    {
	      result[s][r][c] = matrixA[s][r][c] - number;

	    }
	}
    }

  
  return result;

}


struct vec2d subtractMatrix(struct vec2d &matrixA, double number)
{
  int numRows = matrixA.size();
  int numCols = matrixA[0].size();
  vec2d result(numRows,numCols);
  
    for (int row = 0; row < numRows; row++)
    {
      for (int col = 0; col < numCols; col++) 
	{
	  
	  result[row][col] = matrixA[row][col] - number;

	}
    }
  return result;
}


struct vec2d subtractMatrix(double number, struct vec2d &matrixA)
{
  int numRows = matrixA.size();
  int numCols = matrixA[0].size();
  vec2d result(numRows,numCols);
  
    for (int row = 0; row < numRows; row++)
    {
      for (int col = 0; col < numCols; col++) 
	{
	  
	  result[row][col] = matrixA[row][col] - number;

	}
    }
  return result;
}

vector<double> subtractMatrix(vector<double> &matrixA, double number )
{
  int numElements = matrixA.size();

  vector<double> result(numElements);

  for (int n = 0; n < numElements; n++)
    {  
      result[n] = matrixA[n] - number;	
    }
  return result;
}

vector<double> subtractMatrix(double number, vector<double> &matrixA)
{
  int numElements = matrixA.size();

  vector<double> result(numElements);

  for (int n = 0; n < numElements; n++)
    {  
      result[n] = matrixA[n] - number;	
    }
  return result;
}
