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

double G2J(bundle &vars, int j)
{
 double result;
  // Ultimately, G2J = r[j]^3 - r[j-1]^3 -(M[j] - M[j-1])*( 3/ (4 pi rho[j]) )

 if (j==0)
   {
     result = pow(vars.r[j],3)  - (vars.Mwhole[j] * (3.0 / (4.0 *pi * vars.rho[j])));
   }
 else if (j < jMax-1)
   {
     result = pow(vars.r[j],3) - pow(vars.r[j-1],3) - ( (vars.Mwhole[j]-vars.Mwhole[j-1]) * (0.75 / ( pi * vars.rho[j]) ) );

   }
 else
   {
     OneD temp = atmos(vars.r[j], vars.L[j], vars.dMwhole[j], vars.Mwhole[j], vars.EOS);
     result = temp[1] - vars.r[j];
     //     result = vars.r[j] - temp[1];
     //     result = 2.0*vars.r[j] - vars.r[j-1] - temp[1];
     //     result = 2.0*vars.r[j] - vars.r[j-1] - vars.Ratm;
   }
 
 return result;
}


