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

using namespace std;

OneD flattenMatrix(vec3d &matrix)
{
  int length = matrix.size();
  int width = matrix[0].size();
  int height = matrix[0][0].size();
  int index = 0;

  int maxL = width*height;

  OneD result(length*width*height,0);

  for (int l=0; l<length; l++)
    {
      for (int w=0; w<width; w++)
	{
	  for (int h=0; h<height; h++)
	    {
	      result[index] = matrix[l][w][h];
	      index++;
	    }
	}
    }  
  
  return result;
}

OneD flattenMatrix(vec2d &matrix)
{
  int length = matrix.size();
  int width = matrix[0].size();
  int index = 0;

  OneD result(length*width,0);

  for (int w=0; w<width; w++)
    {
      for (int l=0; l<length; l++)
	{
	  result[index] = matrix[l][w];
	  index++;
	}
    }  

  return result;

}
