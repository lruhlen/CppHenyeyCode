#include <iostream>
#include <vector>
#include <math.h>
#include "global.h"
using namespace std;

struct vec2d convert_to_vec2d(vector<vector<double> > &input)
{
  int rows = input.size();
  int cols = input[0].size();
  vec2d output(rows,cols);

  for(int r = 0; r<rows; r++)
    {
      for(int c = 0; c<cols; c++)
	{
	  output[r][c] = input[r][c];
	}
    }

  return output;
}
