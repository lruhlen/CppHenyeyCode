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


vector<double> G3J(bundle &vars)
{

  vector<double> result(jMax);

  // P = vars.x[0]
  // r = vars.x[1]
  // L = vars.x[2]
  // T = vars.x[3]

  // Ultimately, G3J = L[j] - L[j-1] - (M[j]-M[j-1])*( Enuc - (cP[j]*(T[j]-T[j]^n)/delta_t) + (delta/rho[j])*(P[j]-P[j]^n)/delta_t )

  for (int j=0; j < jMax; j++)
    {
      if (j==0)
	{
	  result[j] = vars.x[2][j] - (vars.M[1][j]) *(vars.Enuc[j] - (vars.cP[j]*(vars.x[3][j] - vars.x_old[3][j])/delta_t ) -  ( (vars.delta[j]/vars.rho[j]) * ( (vars.x[0][j]-vars.x_old[0][j])/delta_t )));
	}

      else
	{
	result[j] = vars.x[2][j] - vars.x[2][j-1] - (vars.M[1][j]-vars.M[1][j-1]) *(vars.Enuc[j] - (vars.cP[j]*(vars.x[3][j] - vars.x_old[3][j])/delta_t ) -  ( (vars.delta[j]/vars.rho[j]) * ( (vars.x[0][j]-vars.x_old[0][j])/delta_t )));
      }

    }

  return result;
}


vector<double> G3J(bundle &vars, bundle &varied_vars, int varied_param_index, int offset)
{


  vector<double> result(jMax);
  double temp;
  // P = vars.x[0]
  // r = vars.x[1]
  // L = vars.x[2]
  // T = vars.x[3]

  // Ultimately, G3J = L[j] - L[j-1] - (M[j]-M[j-1])*( Enuc - (cP[j]*(T[j]-T[j]^n)/delta_t) + (delta/rho[j])*(P[j]-P[j]^n)/delta_t )

  for (int j=0; j <jMax ; j++)
    {
      // Deal with the offset variation business
      if ((j+offset > 0) || (j+offset <= jMax))
	{
	  temp = vars.x[varied_param_index][j+offset];
	  vars.x[varied_param_index][j+offset] = varied_vars.x[varied_param_index][j+offset];
	}

      if (j==0) // Again, this boundary condition may not be formulated correctly...
	{
	  result[j] = vars.x[2][j] - (vars.M[1][j]) *(vars.Enuc[j] - (vars.cP[j]*(vars.x[3][j] - vars.x_old[3][j])/delta_t ) -  ( (vars.delta[j]/vars.rho[j]) * ( (vars.x[0][j]-vars.x_old[0][j])/delta_t )));
	}

      else
	{
	result[j] = vars.x[2][j] - vars.x[2][j-1] - (vars.M[1][j]-vars.M[1][j-1]) *(vars.Enuc[j] - (vars.cP[j]*(vars.x[3][j] - vars.x_old[3][j])/delta_t ) -  ( (vars.delta[j]/vars.rho[j]) * ( (vars.x[0][j]-vars.x_old[0][j])/delta_t )));
      }

      // Finish dealing with the offset variation business
      if ((j+offset > 0) || (j+offset <= jMax))
	{
	  vars.x[varied_param_index][j+offset] = temp;
	}


    }

  return result;


}
