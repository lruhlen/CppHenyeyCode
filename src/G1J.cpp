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


vector<double> G1J(bundle &vars)
{

  vector<double> result(jMax);

  // P = vars.x[0]
  // r = vars.x[1]
  // L = vars.x[2]
  // T = vars.x[3]

  for (int j=0; j < jMax; j++)
    {
      if (j+1 < jMax)
	{
	  result[j] = vars.x[0][j+1] - vars.x[0][j] +( (gravG*vars.M[1][j])*(vars.M[0][j+1]-vars.M[0][j]) / (4.0*pi*pow(vars.x[1][j],4.0) )  );
	}
      else
	{
	  result[j] =  vars.x[0][j] +( (gravG*vars.M[1][j])*(vars.M[0][j]) / (4.0*pi*pow(vars.x[1][j],4.0) )  );
	}

    }

  return result;
}



vector<double> G1J(bundle &vars, bundle &varied_vars, int varied_param_index, int offset)
{  
  vector<double> result(jMax);
  double temp;

  for (int j=0; j <jMax ; j++)
    {

      // Deal with the offset variation business
      if ((j+offset > 0) || (j+offset <= jMax))
	{
	  temp = vars.x[varied_param_index][j+offset];
	  vars.x[varied_param_index][j+offset] = varied_vars.x[varied_param_index][j+offset];
	}



      // Then, deal with calculating the result, looping over all j's
      if (j+1 < jMax)
	{
	  result[j] = vars.x[0][j+1] - vars.x[0][j] +( (gravG*vars.M[1][j])*(vars.M[0][j+1]-vars.M[0][j]) / (4.0*pi*pow(vars.x[1][j],4.0) )  );
	}

      else
	{
	  // This bit isn't quite right, maybe?...
	  result[j] =  vars.x[0][j] +( (gravG*vars.M[1][j])*(vars.M[0][j]) / (4.0*pi*pow(vars.x[1][j],4.0) )  );
	}
      

      // Finish dealing with the offset variation business
      if ((j+offset > 0) || (j+offset <= jMax))
	{
	  vars.x[varied_param_index][j+offset] = temp;
	}


    }

  return result;

}
