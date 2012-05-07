#include <vector>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"

using namespace std;

void matrixImplant(OneD &smallMatrix, vec2d &bigMatrix, int index)
{
  int i_size = smallMatrix.size();

  for (int i=0; i<i_size; i++)
    {
      bigMatrix[i][index] = smallMatrix[i];
    }
  
}

void matrixImplant(vec2d &smallMatrix, vec3d &bigMatrix, int index)
{
  int i_size = smallMatrix.size();
  int k_size = smallMatrix[0].size();

  for (int i=0; i<i_size; i++)
    {
      for (int k=0; k<k_size; k++)
	{
	  bigMatrix[i][k][index] = smallMatrix[i][k];
	}
    }


}
