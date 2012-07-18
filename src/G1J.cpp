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


double G1J(bundle &vars, int j)
{

  double result;
  if (j+1 < jMax)
    {
      result = (vars.P[j+1] - vars.P[j]) + ( (gravG*vars.Mwhole[j])*(vars.dMwhole[j]+vars.dMwhole[j+1]) / (8.0*pi*pow(vars.r[j],4.0))  );
      //      result = vars.P[j+1] - vars.P[j] +( (gravG*vars.Mwhole[j])*(vars.Mhalf[j+1]-vars.Mhalf[j]) / (4.0*pi*pow(vars.r[j],4.0) )  );
    }
  else
    {
      result =  vars.P[j] +( (gravG*vars.Mwhole[j])*(vars.dMhalf[j]) / (4.0*pi*pow(vars.r[j],4.0) )  );
    }
  
  return result;
}

