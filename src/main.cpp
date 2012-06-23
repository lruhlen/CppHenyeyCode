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
//#include "flattenMatrix.h"
//#include "unflattenMatrix.h"
#include "matrixTranspose.h"
#include "dotProduct.h"
#include "addMatrix.h"
#include "subtractMatrix.h"
#include "matrixMultiply.h"
//#include "matrixDivide.h"
// #include "matrixExtract.h"
// #include "matrixImplant.h"
// #include "FindInMatrix.h"
// #include "convert_to_vec2d.h"
// #include "convert_from_vec2d.h"
// #include "FindMax.h"
// #include "FindNonZeroMax.h"
// #include "FindMin.h"
// #include "FindNonZeroMin.h"
// #include "matrixInvert.h"
// #include "cleanMatrix.h"
// #include "printMatrixToFile.h"
//#include "PartialDeriv.h"
//#include "G1Jprime.h"
//#include "G2Jprime.h"
//#include "G3Jprime.h"
//#include "G4Jprime.h"
//#include "CalcCDEGprime.h"
//#include "CalcCDEGprime2sided.h"
//#include "HenyeyPrimeMatrixInversion.h"
//#include "MakeHenyeyMatrix.h"
//#include "CalcError.h"
//#include "RescaleCorrections.h"
#include "pause_for_user.h"
//#include "plot_bundle.h"
//#include "plot.h"
#include "atmos.h"
using namespace std;


int main()
{
  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  //Start of:
  // Setting things up
  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  
  //#######################################
  // Read in physical constants and other 
  // specifications for this particular
  // run of the code (output filenames, 
  // number of timesteps, etc.)
  // 
  // Actually, all of that info is already
  // included, via the physicalConstants.h
  // and AboutThisRun.h headers!
  //#######################################
  
  
  //#######################################
  // Declare variables
  //#######################################
  
  // Note:
  //    i = 1/0 = P (pressure)
  //    i = 2/1 = r (radius)
  //    i = 3/2 = L (luminosity)
  //    i = 4/3 = T (temperature)
  
  bundle vars;
  vars.read_in_vars("/Users/laurel/Desktop/Research/CppHenyeyCode/InitialConds/10MjInput.txt");

  TableGroup eos;
  // Read in the kludgy low-temperature & low-pressure eos table
  // Remember: in these tables xvals = log10(P), yvals = log10(T)
  eos.rho.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/CodingSandbox/eos_tables/rhoTableKludge700.txt";
  eos.rho.read_in(700,700);

  eos.cp.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/CodingSandbox/eos_tables/cPtableKludge700.txt";
  eos.cp.read_in(700,700);

  eos.delta.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/CodingSandbox/eos_tables/deltatableKludge700.txt";
  eos.delta.read_in(700,700);

  eos.kappa.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/CodingSandbox/opacity_tables/kappaKludge700.txt";
  eos.kappa.read_in(700,700);
  
  vars.EOS = eos;

  cout<<"Done!\n";
  


  return 0;
} 
