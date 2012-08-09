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

double G2J(bundle &vars, int j)
{

 double result;
  // Ultimately, G2J = r[j]^3 - r[j-1]^3 -(M[j] - M[j-1])*( 3/ (4 pi rho[j]) )

 if (j==0)
   {
     result = pow(vars.r[j],3)  - (vars.Mwhole[j] * (3.0 / (4.0 *pi * vars.rho[j])));
     // cout<<"\nG2J calcs:\n";
     // cout<<"\tR^3 = "<<pow(vars.r[j],3)<<endl;
     // cout<<"\tSecond part = "<<-1.0* (vars.Mwhole[j] * (3.0 / (4.0 *pi * vars.rho[j])))<<endl;
     // cout<<"\t\t(vars.Mwhole[j] ) =  "<<vars.Mwhole[j]<<endl;
     // cout<<"\t\t (3.0 / (4.0 *pi * vars.rho[j])) =  "<<(3.0 / (4.0 *pi * vars.rho[j]))<<endl;
   }
 
 else
   {
     result = pow(vars.r[j],3) - pow(vars.r[j-1],3) - ((vars.Mwhole[j]-vars.Mwhole[j-1]) * (3.0 / (4.0 *pi * vars.rho[j])));
   }
 
 return result;
}


