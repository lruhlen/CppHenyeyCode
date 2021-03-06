#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "printVector.h"
#include "printMatrix.h"
#include "FindMax.h"
#include <float.h>
#include "cleanMatrix.h"

using namespace std;

vec3d matrixDivide(vec3d &matrixA, vec3d &matrixB)
{
  int x = matrixA.size();
  int y = matrixA[0].size();
  int z = matrixA[0][0].size();
  vec3d result(x,y,z);

  for (int i=0; i<x; i++)
    {
      for (int j=0; j<y; j++)
	{
	  for (int k=0; k<z; k++)
	    {
	      if((matrixA[i][j][k] == 0) && (matrixB[i][j][k]==0))
		{
		  result[i][j][k] = 0.0;
		}
	      else
		{
		  result[i][j][k] = matrixA[i][j][k] / matrixB[i][j][k];
		}
	    }
	}
    }
  return result;

}


vec2d matrixDivide(vec2d &matrixA, vec2d &matrixB)
{
  int x = matrixA.size();
  int y = matrixA[0].size();

  vec2d result(x,y);

  for (int i=0; i<x; i++)
    {
      for (int j=0; j<y; j++)
	{
	  if((matrixA[i][j] == 0) && (matrixB[i][j]==0))
	    {
	      result[i][j] = 0.0;
	    }
	  else
	    {
	      result[i][j] = matrixA[i][j] / matrixB[i][j];
	    }
	}
    }
  return result;

}



vector<double> matrixDivide(vector<double> &matrixA, vector<double> &matrixB)
{
  int x = matrixA.size();
  
  vector<double> result(x);

  for (int i=0; i<x; i++)
    {
      if((matrixA[i] == 0) && (matrixB[i]==0))
	{
	  result[i] = 0.0;
	}
      else
	{
	  result[i] = matrixA[i] / matrixB[i];
	}
    }
  return result;

}

vec3d matrixDivide(double &A, vec3d &matrixB)
{
  int x = matrixB.size();
  int y = matrixB[0].size();
  int z = matrixB[0][0].size();
  vec3d result(x,y,z);

  for (int i=0; i<x; i++)
    {
      for (int j=0; j<y; j++)
	{
	  for (int k=0; k<z; k++)
	    {
	      result[i][j][k] = matrixB[i][j][k] / A;
	    }
	}
    }

  return result;

}


vec2d matrixDivide(double &A, vec2d &matrixB)
{  
  int x = matrixB.size();
  int y = matrixB[0].size();

  vec2d result(x,y);

  for (int i=0; i<x; i++)
    {
      for (int j=0; j<y; j++)
	{
	  result[i][j] = matrixB[i][j] / A;

	}
    }
  return result;



}

vector<double> matrixDivide(double &A, vector<double> &matrixB)
{
  int x = matrixB.size();
  
  vector<double> result(x);

  for (int i=0; i<x; i++)
    {
	  result[i] = matrixB[i] / A;
    }

  return result;

}
