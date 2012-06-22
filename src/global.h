#ifndef GLOBAL_H
#define GLOBAL_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "printMatrix.h"
#include "pause_for_user.h"
#include <algorithm>
using namespace std;
//====================================================
// Random useful info that needs to be passed around
//====================================================



//====================================================
//Define the two and three-D vector machinary
//====================================================
typedef vector<double> OneD;
typedef vector<vector<double> > TwoD;
typedef vector<TwoD> ThreeD;

//----------------------------------------------------
// Both of these structs have overloaded constructors.
// You can create vec2d/3d with or without specifying 
// their dimensions.
//----------------------------------------------------

struct vec2d: public TwoD
{
  vec2d():TwoD() {};
  vec2d(int m, int n):TwoD(m,OneD(n)){};
  vec2d(int m, int n, double d): TwoD(m,OneD(n,d)) {}  
};
// Giving up on trying to code "methods" into this "class" or whatever, for now.

struct vec3d: public std::vector<vec2d>
{
  vec3d():std::vector<vec2d>() {};
  vec3d(int m, int n, int k):std::vector<vec2d>(m,vec2d(n,k)) {};
  vec3d(int m, int n, int k, double d):std::vector<vec2d>(m,vec2d(n,k,d)) {}
};



/* 
===============================================
 Make a general table class with lookup,
 bilinear interpolation, and... readin? methods
=============================================== */
class Table
{
 public:
  // Variable declarations
  string table_name;
  //  vec3d IndepVarsGrid;
  //  vec3d DepVarsGrid;

  // Function declarations
  void read_in(int numXvals, int numYvals); 
  OneD xvals, yvals;
  vec2d gridvals;

  // The general look-up function
  vec2d lookup(double IndepVar1, double IndepVar2);
  //  vec2d old_lookup(double IndepVar1, double IndepVar2);

  // The bilinear interpolation function
  double bilinear_interp(double IndepVar1, double IndepVar2);
  //  double old_bilinear_interp(double IndepVar1, double IndepVar2, int DepVarIndex);
  
  //  double IndepVar1_min, IndepVar1_max, IndepVar2_min, IndepVar2_max;
  // These will be set by the read-in function...

  // A method that will prints the table's contents
  void printTable();


};

// For passing a group of tables that describe a particular system's total EOS
class TableGroup : public Table
{
 public:
  // variable declarations
  Table cp, delta, rho, kappa;

  // function declarations
  // want something that will look up everything that depends on P and T only and return all those values...
  OneD lookup(double P, double T);
};


//====================================================
// Make a class that "bundles" variables together,
// for transport between functions
//====================================================

class bundle : public TableGroup
{
 public:
  // Variable declarations
  vec2d x, dx, x_old, dx_old, xprime, dxprime, xprime_old, dxprime_old; 
  vec2d M;
  vector<double> rho;
  vector<double> delta;
  vector<double> rad_grad;
  vector<double> ad_grad;
  vector<double> grad;
  vector<double> cP;
  vector<double> kappa;
  vector<double> internal_energy;
  vector<double> Enuc;

  TableGroup EOS;
  

  // Function declarations
  void read_in_vars(int varnum, string filename);
//   void update_vars(bool is_the_update_xprime_based);
 
};

#endif
