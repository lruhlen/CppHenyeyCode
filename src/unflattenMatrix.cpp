#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>
#include <float.h>
#include "global.h"
#include "printMatrix.h"
using namespace std;

vec2d unflattenMatrix(OneD &array, int i_index, int j_index)
{
  vec2d result(i_index,j_index,0);
  int counter = 0;

  for (int j=0; j<j_index; j++)
    {
      for (int i=0; i<i_index; i++)
	{
	  result[i][j] = array[counter];
	  counter++;
	}
    }
  
  return result;
}

vec3d unflattenMatrix(OneD &array, int i_index, int j_index, int k_index)
{
  vec3d result(i_index,j_index,k_index,0);
  int counter = 0;

  for (int k=0; k<k_index; k++)
    {
      for (int j=0; j<j_index; j++)
	{
	  for (int i=0; i<i_index; i++)
	    {
	      result[i][j][k] = array[counter];
	      counter++;
	    }
	}
    }

  return result;
}


vec2d unflattenMatrix(vec2d &array, int i_index, int j_index)
{  
  
  vec2d result(i_index,j_index,0);
  int counter = 0;

  for (int j=0; j<j_index; j++)
    {
      for (int i=0; i<i_index; i++)
	{
	  result[i][j] = array[counter][0];
	  counter++;
	}
    }

  return result;
}

vec3d unflattenMatrix(vec2d &array, int i_index, int j_index, int k_index)
{
  vec3d result(i_index,j_index,k_index,0);
  int counter = 0;

  for (int k=0; k<k_index; k++)
    {      
      for (int j=0; j<j_index; j++)
	{
	  
	  for (int i=0; i<i_index; i++)
	    {
	      result[i][j][k] = array[counter][0];
	      counter++;
	    }
	}
    }

  return result;
}
