#include <iostream>
#include <vector>
#include <math.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "convert_to_vec2d.h"
#include "convert_from_vec2d.h"
#include "printMatrix.h"

using namespace std;

double G4J(bundle &vars, int j)
{

  double result;
  double Bj, Bj1;
      if (j+1 < jMax)
	{
	  Bj = vars.grad[j] * vars.T[j] / vars.P[j];
	  Bj1 =vars.grad[j+1] * vars.T[j+1] / vars.P[j+1];
	  
	  result = vars.T[j+1] - vars.T[j] + (gravG * vars.Mwhole[j] *(vars.Mhalf[j+1]-vars.Mhalf[j])/ (8.0* pi *pow(vars.r[j],4.0)) * (Bj1+Bj));
	}
      else
	{
	  Bj = vars.grad[j] * vars.T[j] / vars.P[j];
	  result =  vars.T[j] + (gravG * vars.Mwhole[j] *(vars.Mhalf[j])/ (8.0* pi *pow(vars.r[j],4.0)) * Bj);
	}

  return result;
}





