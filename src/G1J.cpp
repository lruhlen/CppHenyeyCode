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


double G1J(bundle &vars, int j)
{

  double result;
  if (j+1 < jMax)
    {
      result = (vars.P[j+1] - vars.P[j]) + ( (gravG*vars.Mwhole[j])*(vars.dMwhole[j]+vars.dMwhole[j+1]) / (8.0*pi*pow(vars.r[j],4.0))  );
      //      cout<<vars.P[j+1]<<"\t"<<vars.P[j]<<"\t";
      //      cout<<(vars.P[j+1] - vars.P[j]) <<"\n";
      //      cout<<  (gravG*vars.Mwhole[j])<<"\t"<<(vars.dMwhole[j]+vars.dMwhole[j+1]) / (8.0*pi*pow(vars.r[j],4.0))  <<endl;
    }
  else
    {
      OneD temp = atmos(vars.r[j], vars.L[j], vars.dMwhole[j], vars.Mwhole[j], vars.EOS);
      result = temp[2] - vars.P[j];
      //      result =  vars.P[j] - vars.Patm;
      //      result = vars.P[j] - temp[2];
    }

  return result;
}

