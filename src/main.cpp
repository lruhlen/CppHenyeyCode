#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>
#include <float.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "printVector.h"
#include "printMatrix.h"
#include "matrixTranspose.h"
#include "dotProduct.h"
#include "addMatrix.h"
#include "subtractMatrix.h"
#include "matrixMultiply.h"
#include "G1J.h"
#include "G2J.h"
#include "G3J.h"
#include "G4J.h"
#include "NewCalcCDEG.h"
#include "modifiedHenyeyMatrixInversion.h"
#include "pause_for_user.h"
#include "atmos.h"
using namespace std;


int main()
{

  // Note:
  //    i = 1/0 = P (pressure)
  //    i = 2/1 = r (radius)
  //    i = 3/2 = L (luminosity)
  //    i = 4/3 = T (temperature)
  
  // // Read in the starting conditions
   bundle vars;
  // Read in the EOS and opacity table info
  TableGroup eos;


  // Read in the kludgy low-temperature & low-pressure eos table
  // Remember: in these tables xvals = log10(P), yvals = log10(T)
  eos.rho.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/rho1000.txt";
  eos.rho.read_in(1000,1000);  
  eos.cp.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/cP1000.txt";
  eos.cp.read_in(1000,1000);  
  eos.delta.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/delta1000.txt";
  eos.delta.read_in(1000,1000);  
  eos.kappa.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/opacity_tables/kappa1000.txt";
  eos.kappa.read_in(1000,1000);   
  cout<<"\nDone reading in eos tables\n";
  vars.EOS = eos;  
  cout<<"\nDone setting the vars eos tables\n";
  
  vars.read_in_vars("/Users/laurel/Desktop/Research/CppHenyeyCode/InitialConds/10MjupInput.txt");
  cout<<"\nDone reading in vars\n";
  
  vars.eos_var_update(-1);
  cout<<"\nDone setting the lookup/update eos vars!\n";

  atmos(vars.r[jMax-1], vars.L[jMax-1], vars.dMwhole[jMax-1], vars.Mwhole[jMax-1], vars.EOS);
  cout<<"\nDone running the atmos subroutine!\n";

  vec2d G(jMax,iMax,0);
  vec3d C(jMax,iMax,iMax,0), D(jMax,iMax,iMax,0),E(jMax,iMax,iMax,0);
  NewCalcCDEG(vars, G, C, D, E);
  cout<<"\nDone running the NewCalcCDEG subroutine!\n";
  
  // Test out the Henyey Matrix inversion routine
  modifiedHenyeyMatrixInversion(vars,C,D,E,G);
  cout<<"\nDone running the Henyey Matrix inversion subroutine!\n";
  cout<<"\nHere are the corrections to the first few cells:\n";
  cout<<"dP: "; printMatrix(vars.dP,jMax-5,jMax); cout<<endl;
  cout<<"dr: "; printMatrix(vars.dr,jMax-5,jMax); cout<<endl; 
  cout<<"dL: "; printMatrix(vars.dL,jMax-5,jMax); cout<<endl;  
  cout<<"dT: "; printMatrix(vars.dT,jMax-5,jMax); cout<<endl;

  cout<<"\nDone!\n";

  
  
  return 0;
} 
