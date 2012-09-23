#include <iostream>
#include <vector>
#include <math.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "convert_to_vec2d.h"
#include "convert_from_vec2d.h"
#include "printMatrix.h"
#include "atmos.h"

using namespace std;

double G4J(bundle &vars, int j)
{

  double result;
  double Bj, Bj1;
      if (j+1 < jMax)
	{
	  Bj = vars.grad[j] * vars.T[j] / vars.P[j];
	  Bj1 =vars.grad[j+1] * vars.T[j+1] / vars.P[j+1];
	  
	  result = (vars.T[j+1] - vars.T[j]) - ( (vars.P[j+1] - vars.P[j]) * (Bj1+Bj)/2.0);
	}
      else
	{
	  OneD temp = atmos(vars.r[j], vars.L[j], vars.dMwhole[j], vars.Mwhole[j], vars.EOS);

	  result = vars.T[j] - temp[3];
	  //	  result = vars.T[j] - vars.Tatm;
	  
	}

  return result;
}





