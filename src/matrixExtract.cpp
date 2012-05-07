#include <vector>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"

using namespace std;

OneD matrixExtract(vec2d &bigMatrix, int index)
{
  int size = bigMatrix.size();
  
  OneD result(size,0);

  for (int x=0; x<size; x++)
    {
      result[x] = bigMatrix[x][index];
    }

  return result;
}


vec2d matrixExtract(vec3d &bigMatrix, int index)
{
  int i_size = bigMatrix.size();
  int k_size = bigMatrix[0].size();
  
  vec2d result(i_size,k_size,0);

  for (int i = 0; i<i_size; i++)
    {
      for (int k=0; k<k_size; k++)
	{
	  result[i][k] = bigMatrix[i][k][index];
	}
    }

  return result;
}
