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


vector<double> G2J(bundle &vars)
{

  vector<double> result(jMax);

  // P = vars.x[0]
  // r = vars.x[1]
  // L = vars.x[2]
  // T = vars.x[3]

  // Ultimately, G2J = r[j]^3 - r[j-1]^3 -(M[j] - M[j-1])*( 3/ (4 pi rho[j]) )

  for (int j=0; j < jMax; j++)
    {
      if (j==0)
	{
	  result[j] = pow(vars.x[1][j],3)  - ((vars.M[1][j]) * (3.0 / (4.0 *pi * vars.rho[j])));
	}
      
      else
	{
	  result[j] = pow(vars.x[1][j],3) - pow(vars.x[1][j-1],3) - ((vars.M[1][j]-vars.M[1][j-1]) * (3.0 / (4.0 *pi * vars.rho[j])));
	}

    }

  return result;
}


vector<double> G2J(bundle &vars, bundle &varied_vars, int varied_param_index, int offset)
{

  vector<double> result(jMax);
  double temp;
  // P = vars.x[0]
  // r = vars.x[1]
  // L = vars.x[2]
  // T = vars.x[3]

  // Ultimately, G2J = r[j]^3 - r[j-1]^3 -(M[j] - M[j-1])*( 3/ (4 pi rho[j]) )

  for (int j=0; j <jMax ; j++)
    {

      // Deal with the offset variation business
      if ((j+offset > 0) || (j+offset <= jMax))
	{
	  temp = vars.x[varied_param_index][j+offset];
	  vars.x[varied_param_index][j+offset] = varied_vars.x[varied_param_index][j+offset];
	}

      if (j==0) // Again, this boundary condition may not be exactly right...
	{
	  result[j] = pow(vars.x[1][j],3)  - ((vars.M[1][j]) * (3.0 / (4.0 *pi * vars.rho[j])));
	}
      
      else  
	{
	  result[j] = pow(vars.x[1][j],3) - pow(vars.x[1][j-1],3) - ((vars.M[1][j]-vars.M[1][j-1]) * (3.0 / (4.0 *pi * vars.rho[j])));
	}


       // Finish dealing with the offset variation business
      if ((j+offset > 0) || (j+offset <= jMax))
	{
	  vars.x[varied_param_index][j+offset] = temp;
	}


    }

  return result;


}
