#include <iostream>
#include <vector>
#include <math.h>
#include "global.h"
using namespace std;

vector<vector<double> > convert_from_vec2d(struct vec2d &input)
{
  int rows = input.size();
  int cols = input[0].size();
  vector<vector<double> > output(rows,cols);

  for(int r = 0; r<rows; r++)
    {
      for(int c = 0; c<cols; c++)
	{
	  output[r][c] = input[r][c];
	}
    }

  return output;
}
