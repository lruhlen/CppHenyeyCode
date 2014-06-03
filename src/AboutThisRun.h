#ifndef ABOUTTHISRUN_H 
#define ABOUTTHISRUN_H
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std; 
/* ==============================================
   This should be the only file the user modifies
   from one run to the next.

   It will contain settings for the output file
   name-root, the total time range that the 
   observation should cover, values for delta_t,
   and anything else that you might want to twiddle 
   from one run to the next.
   ============================================== */

const double Tmax = 0.0;
//const double delta_t = 0.0;
//const double delta_t = 1.0e11; // this is about 3000 years...
//const double delta_t = 3.4789e9;
//const double delta_t = 1.00;
const double delta_t = 1.00e8;
const double tolerance = 1e-4;
//const double epsilon = 0.1; // Setting the upper limit for the size of corrections to apply to the dependent variables 
//const int jMax = 298;
const int jMax = 551;
//const int jMax = 6;
const int iMax = 4;
const int kMax = 4;
const int lMax = 4;
const int mMax = 4;
const double polytropic_gamma = 2.0; 




// Set the level of debugging statements to ignore/print out.
const int debugflag = 4;
const string temp_plot_path = "/Users/laurel/Desktop/Research/CppHenyeyCode/CodingSandbox/debugging_graphs/temp/";
const string plot_path = "/Users/laurel/Desktop/Research/CppHenyeyCode/CodingSandbox/debugging_graphs/temp/";


#endif
