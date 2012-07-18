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


double G3J(bundle &vars, int j)
{

  double result;
  double Tinverse = 0;
  if (delta_t != 0)
    {
      Tinverse = 1.0/delta_t;
    }
  

  // Ultimately, G3J = L[j] - L[j-1] - (M[j]-M[j-1])*( Enuc - (cP[j]*(T[j]-T[j]^n)/delta_t) + (delta/rho[j])*(P[j]-P[j]^n)/delta_t )
  if (j==0)
    {
      result = vars.L[j] - (vars.dMwhole[j]) *(vars.Enuc[j] - (vars.cP[j]*(vars.T[j] - vars.oldT[j])*Tinverse) -  ( (vars.delta[j]/vars.rho[j]) * ( (vars.P[j]-vars.oldP[j])* Tinverse)));
    }
  else
    {
      result = vars.L[j] - vars.L[j-1] - (vars.dMwhole[j]) *(vars.Enuc[j] - (vars.cP[j]*(vars.T[j] - vars.oldT[j])*Tinverse ) -  ( (vars.delta[j]/vars.rho[j]) * ( (vars.P[j]-vars.oldP[j])*Tinverse )));
    }
  
  return result;
}

