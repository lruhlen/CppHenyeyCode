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
const double delta_t = 3.2e10; // this is about 1000 years...
const double tolerance = 1e-4;
const double epsilon = 0.1; // Setting the upper limit for the size of corrections to apply to the dependent variables 
//const int jMax = 200;
const int jMax = 550;
const int iMax = 4;
const int kMax = 4;
const int lMax = 4;
const int mMax = 4;
const double polytropic_gamma = 2.0; 

// Tell the program where your opacity table, eos table, and P/T/L/r initial conditions files are.
const string initial_conds_dir = "/Users/laurel/Desktop/Research/CppHenyeyCode/CodingSandbox/InitialConds/";
const string M_initial_conds = initial_conds_dir +  "MassInitialConds.txt";
const string P_initial_conds = initial_conds_dir + "logPInitialConds.txt";
const string T_initial_conds = initial_conds_dir + "logTInitialConds.txt";
const string L_initial_conds = initial_conds_dir + "LinearLuminosityInitialConds.txt";
const string r_initial_conds = initial_conds_dir + "RadiusInitialConds.txt";

const string eos_table = "/Users/laurel/Desktop/Research/CppHenyeyCode/CodingSandbox/eos_tables/H_TAB_I.A";
const string opacity_table = "/Users/laurel/Desktop/Research/CppHenyeyCode/CodingSandbox/opacity_tables/opac.cool";


// For if/when you want to calculate the eqn of state analytically.
// Placeholder for the EOS tables: tells the lookup function to 
// stop once it reaches this value.
// Have to have this kludge, because there's no way to have a 
// 'ragged' table, with rows of different lengths.
const double ignore_flag = -1.0e7; 
const int max_num_T_bins = 63;
const int max_num_P_bins = 76;


// Set the level of debugging statements to ignore/print out.
const int debugflag = 2;
const string temp_plot_path = "/Users/laurel/Desktop/Research/CppHenyeyCode/CodingSandbox/debugging_graphs/temp/";
const string plot_path = "/Users/laurel/Desktop/Research/CppHenyeyCode/CodingSandbox/debugging_graphs/temp/";


#endif
