#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "printMatrix.h"
#include <float.h>


using namespace std;
//====================================================
// Table method definitions
//====================================================

void Table::read_in()
{
//   IndepVar1_min = 0;
//   IndepVar1_max = 0;
//   IndepVar2_min = 0;
//   IndepVar2_max = 0;
   // cout<<"\n Leaving this method blank for now!\n";
}

vec2d Table::lookup(double IndepVar1, double IndepVar2)
{
  /* This function assumes that both independent variables are
     sorted from lowest to highest.

     For the purposes of the EOS tables, 
     IndepVar1 = Temperature (T)
     IndepVar2 = Pressure (P)
  */

  vec2d corner_indices = vec2d(4,2,-1);

  int var1_low_index = -1, var1_high_index = -1, var2_low1_index = -1, var2_high1_index = -1, var2_low2_index = -1, var2_high2_index = -1;


  // The following two lines are pretty kludge-y
  // and constitute an abstraction violation...
  // Fix this when you have a chance.
  //  int max_num_var1_bins = int(DepVarsGrid.size());
  //  int max_num_var2_bins = int(DepVarsGrid[0].size());
    int max_num_var1_bins = int(DepVarsGrid[0].size());
    int max_num_var2_bins = int(DepVarsGrid[0][0].size());

    //  // cout<<"max_num_var1_bins: "<<max_num_var1_bins<<" \t max_num_var2_bins: "<<max_num_var2_bins<<endl ;

  // Check that IndepVar1 (temperature?) lies within the bounds of this table
  if ( (IndepVar1 < IndepVar1_min) || (IndepVar1 > IndepVar1_max))
    {
      cout<<"ERROR:  The first independent variable ("<< IndepVar1<<") is outside the bounds of this table ("<<IndepVar1_min<< " to "<<IndepVar1_max << ")\n";   
      return corner_indices;
    }

  if ((IndepVar2 < IndepVar2_min) || (IndepVar2 > IndepVar2_max) )
    {
      cout<<"ERROR:  The second independent variable ("<< IndepVar2<<") is outside the bounds of this table ("<<IndepVar2_min<< " to "<<IndepVar2_max << ")\n";   
      return corner_indices;
    }

  else{
    // Start by finding the corners on IndepVar1 within the table
    for (int var1_index = 0; var1_index < max_num_var1_bins; var1_index++)
      {
	if (IndepVar1 == IndepVarsGrid[var1_index][0][0])
	  {
	    /*	  
	      If the value exactly matches one of the table's gridpoints,
	      you can stop the search for the var1 bracketing points!
	    */

	    var1_low_index = var1_index;
	    var1_high_index = var1_index;
	    break;  
	  }
      
	else if (IndepVar1 < IndepVarsGrid[var1_index][0][0])
	  {
	    var1_low_index = var1_index-1;
	    var1_high_index = var1_index;
	    break;
	  }
      }

 
    for (int var2_index = 0; ((IndepVarsGrid[var1_low_index][var2_index][0]!= ignore_flag ) &&  (IndepVarsGrid[var1_low_index][var2_index][1]!= ignore_flag ) && (var2_index < max_num_var2_bins) ); var2_index++)
      {
	if ( IndepVar2 == IndepVarsGrid[var1_low_index][var2_index][1]  )
	  {
	    var2_low1_index = var2_index;
	    var2_high1_index = var2_index;
	    break;
	  }	  
	else if (IndepVar2 < IndepVarsGrid[var1_low_index][var2_index][1])
	  {
	    var2_low1_index = var2_index-1;
	    var2_high1_index = var2_index;
	    break;
	  }
      }


    for (int var2_index = 0; ((IndepVarsGrid[var1_high_index][var2_index][0]!= ignore_flag ) && (IndepVarsGrid[var1_high_index][var2_index][1]!= ignore_flag ) && (var2_index < max_num_var2_bins) ); var2_index++)
      {
	if (IndepVar2 == IndepVarsGrid[var1_high_index][var2_index][1] )
	  {
	    var2_low2_index = var2_index;
	    var2_high2_index = var2_index;
	    break;
	  }	

	else if (IndepVar2 < IndepVarsGrid[var1_high_index][var2_index][1])
	  {
	    var2_low2_index = var2_index-1;
	    var2_high2_index = var2_index;
	    break;
	  }
      }

    if ( (var2_low1_index == -1) || (var2_low2_index == -1) || (var2_high1_index == -1) || (var2_high2_index == -1) )
      {
	cout<<"ERROR: The second independent variable ("<<IndepVar2 << ") lies outside the bounds of this this particular row of IndepVar1 values. \n";

	

	return corner_indices;

      }
     
    // Fill in the corner_indices, and return.
    else
      {
	corner_indices[0][0] = var1_low_index;
	corner_indices[0][1] = var2_low1_index;
	
	corner_indices[1][0] = var1_low_index;
	corner_indices[1][1] = var2_high1_index;

	corner_indices[2][0] = var1_high_index;
	corner_indices[2][1] = var2_low1_index;

	corner_indices[3][0] = var1_high_index;
	corner_indices[3][1] = var2_high2_index;

	//	// cout<<"Printing the corner indicies within the lookup function:\n";
	//	printMatrix(corner_indices);

	return corner_indices;
      }
  }
}

double Table::bilinear_interp(double IndepVar1, double IndepVar2, int DepVarIndex) 
{
  double result;
  double fQ11, fQ12, fQ21, fQ22;
  double x, y, dx, dy, x1, x2, y1, y2, y3, y4;
  x = IndepVar1;
  y = IndepVar2;

  vec2d corner = lookup(x,y);
  
  x1 = IndepVarsGrid[ int(corner[0][0]) ][0][0];
  x2 = IndepVarsGrid[ int(corner[2][0])][0][0];
  y1 = IndepVarsGrid[ int(corner[0][0])][ int(corner[0][1])][1];
  y2 = IndepVarsGrid[ int(corner[1][0])][ int(corner[1][1])][1];
  y3 = IndepVarsGrid[ int(corner[2][0])][ int(corner[2][1])][1];
  y4 = IndepVarsGrid[ int(corner[3][0])][ int(corner[3][1])][1];
  
  //  // cout<<x1<<"\t "<<x2<<"\t"<<y1<<"\t"<<y2<<endl;  

  if ( (y1 != y3) || (y2 != y4) )
    {
      //      // cout<<"WARNING: The y-edges aren't equal...\n";
      y3 = y1;
      y4 = y2;
    }

  dx = x2-x1; // // cout<<"dx: "<<dx<<endl;
  dy = y2-y1; //// cout<<"dy: "<<dy<<endl;
  // // cout<<"DepVarIndex is: "<<DepVarIndex<<endl;

  fQ11 = DepVarsGrid[ DepVarIndex ][ int(corner[0][0])][int(corner[0][1])]; 
  fQ12 = DepVarsGrid[ DepVarIndex ][ int(corner[2][0])][int(corner[2][1])]; 
  fQ21 = DepVarsGrid[ DepVarIndex ][ int(corner[1][0])][int(corner[1][1])]; 
  fQ22 = DepVarsGrid[ DepVarIndex ][ int(corner[3][0])][int(corner[3][1])]; 
  
  //  // cout<<fQ11<<"\t "<<fQ12<<"\t"<<fQ21<<"\t"<<fQ22<<endl;  

  if ( (dx != 0) && (dy != 0) )
    {
      result = (1.0/(dx*dy)) * ((fQ11 * (x2-x) * (y2-y)) + (fQ21 * (x-x1) * (y2-y)) + (fQ12 * (x2-x) * (y-y1))+ (fQ22 * (x-x1) * (y-y1) )) ;
      //      // cout<<"Case 1 \n";
    }
  else if ( (dx == 0) && (dy != 0))
    {
      result = (1.0/dy) * ((fQ11 * (y2-y)) + (fQ22 * (y-y1)));
      //      // cout<<"Case 2: dx = 0 \n";
    }
  else if ( (dx !=0 ) && (dy == 0) )
    {
      result = (1.0/dx) * ((fQ11 * (x2-x)) + (fQ22 * (x-x1)));
      //      // cout<<"Case 3: dy=0 \n";
      //      // cout<<fQ11<<"\t"<<fQ22<<endl;
    }
  else if ( (dx == 0 ) && (dy == 0) )
    {
      result = fQ11;
      //     // cout<<"Case 4: dx=dy=0 \n";
    }

  //   // cout<<endl<<"For comparison, the unweighted avg. is: "<<(fQ11+fQ12+fQ21+fQ22)/4.0<<endl;

  return result;
}

//====================================================
// EOStable method definitions
//====================================================

void EOStable::read_in()
{

  string line, foo;
  i_rho = 0, i_internal_energy=1, i_ad_grad = 2, i_delta = 3;
 
  int P_index = 0; 
  int T_index = -1;
  int max_P_index = 0;
 
  double log_P_value;
  double log_T_value;

  double min_P_value, max_P_value, min_T_value, max_T_value;
  ifstream myfile(table_name.c_str());
  stringstream ss;

  IndepVarsGrid = vec3d(max_num_T_bins,max_num_P_bins,2,ignore_flag);
  // This is the grid of P vs. T, which are the indep vars for this type of table
  DepVarsGrid = vec3d(max_num_T_bins,max_num_P_bins,4,ignore_flag);

  

  vec2d rho = vec2d(max_num_T_bins,max_num_P_bins,ignore_flag);
  vec2d internal_energy = vec2d(max_num_T_bins,max_num_P_bins,ignore_flag);
  vec2d ad_grad = vec2d(max_num_T_bins,max_num_P_bins,ignore_flag);
  vec2d delta = vec2d(max_num_T_bins,max_num_P_bins,ignore_flag);

  if (myfile.is_open())
    {
      while (! myfile.eof())
	{	

	  // Read in the line of data from the table file
	  
	  while (getline(myfile,line))
	    {
	      ss.clear();
	      ss.str(line);
	      ss >> ws;

	      if(line.size() < 20)
		{
		  P_index = 0;
		  T_index++;

		  ss >> foo;
		  log_T_value = atof(foo.c_str());
		  ss >> foo;
		  max_P_index = atoi(foo.c_str());


		}
	      else
		{

		  IndepVarsGrid[T_index][P_index][0]= log_T_value; 

		  ss >> foo;
		  IndepVarsGrid[T_index][P_index][1]= atof(foo.c_str());
		  
		  ss>>foo>>foo>>foo;
		  rho[T_index][P_index] = atof(foo.c_str());

		  ss>>foo>>foo;
		  internal_energy[T_index][P_index] = atof(foo.c_str());
		  
		  ss>>foo;
		  delta[T_index][P_index] = atof(foo.c_str());
		  
		  ss>>foo>>foo>>foo>>foo; 
		  ad_grad[T_index][P_index] = atof(foo.c_str());
		  
		  if ((P_index == 0) || (T_index == 0))
		    {
		      min_P_value = IndepVarsGrid[0][0][1];
		      max_P_value = IndepVarsGrid[0][0][1];
		    }
		  else 
		    {
		      if (IndepVarsGrid[T_index][P_index][1] < min_P_value)
			{
			  min_P_value = IndepVarsGrid[T_index][P_index][1];
			}
		      if (IndepVarsGrid[T_index][P_index][1] > max_P_value)
			{
			  max_P_value = IndepVarsGrid[T_index][P_index][1];
			}
		    }
		  
		  P_index++;
		}
	    }
	  max_T_value = IndepVarsGrid[T_index][0][0];
	  min_T_value = IndepVarsGrid[0][0][0];

	}
      }
  else 
    {
      // cout<<"Can't find the EOS table you want us to read in. \n Check the path you gave us? \n\n";
    }

  //  // cout<<"Temperature range: "<<min_T_value<<" to "<<max_T_value<<endl;
  // // cout<<"Pressure range: "<<min_P_value<<" to "<<max_P_value<<endl;

  IndepVar1_min = min_T_value;
  IndepVar1_max = max_T_value;

  IndepVar2_min = min_P_value;
  IndepVar2_max = max_P_value;

  DepVarsGrid[i_rho] = rho;
  DepVarsGrid[i_internal_energy] = internal_energy;
  DepVarsGrid[i_ad_grad] = ad_grad;
  DepVarsGrid[i_delta] = delta;

}

//...................................................

//====================================================
// Opacitytable method definitions
//====================================================

void Opacitytable:: read_in()
{  
  string line, foo;
  i_kappa = 0;
 
  OneD Rvals = OneD(19);
  OneD Tvals = OneD(70);
  int R_index = 0;
  int T_index = 0;
  int R_range = 19;
  int T_range = 70;
  bool not_in_header = false;
  int max_R_index = 0;
  double log_R_value, log_T_value;
  double min_T_value, max_T_value, min_R_value, max_R_value;
  ifstream myfile(table_name.c_str());
  stringstream ss;

  // This is the grid of R vs. T, which are the indep vars for this type of table
  // 70 T values per table, 19 R values per table (according to the OPAL specifications, at least)
  IndepVarsGrid = vec3d(70,19,2,ignore_flag);
  DepVarsGrid = vec3d(70,19,1,ignore_flag);
  vec2d kappa = vec2d(70,19,ignore_flag);
 
  if (myfile.is_open())
    {
      while (! myfile.eof())
	{	

	  // Read in the line of data from the table file	  
	  while (getline(myfile,line))
	    {
	      /* Skip empty lines */
	      if (line == "")
		{
		  continue;
		}
	      
	      ss.clear();
	      ss.str(line);
	      // Get rid of white space between the adjacent elements.
	      ss >> ws;
	      ss >> foo;

	      // Ignore all of the stuff in the header
	      if (foo == "logT") /* Read in the R values in that first line of the table */
		{
		  not_in_header = true;
		  for (R_index = 0; R_index < R_range; R_index++)
		    {
			  ss>>foo;
			  Rvals[R_index] = atof(foo.c_str());
			  // Check for min and max R values
			  if (R_index == 0) {
			    min_R_value = Rvals[R_index];
			    max_R_value = Rvals[R_index];
			  }
			  if ( (Rvals[R_index] < min_R_value) && (R_index > 0)) {min_R_value = Rvals[R_index];}
			  if ( (Rvals[R_index] > max_R_value) && (R_index > 0)) {max_R_value = Rvals[R_index];}
			  
		    }
		}
	      else if (not_in_header) /* Read in the T values */
		{
		  Tvals[T_index] =  atof(foo.c_str());		  
		  // Check for min and max T values
		  if (T_index == 0)
		    {
		      min_T_value = Tvals[T_index];
		      max_T_value = Tvals[T_index];
		    }
		  if ((Tvals[T_index] < min_T_value) && (T_index > 0)){min_T_value = Tvals[T_index];}
		  if ((Tvals[T_index] > max_T_value) && (T_index > 0)){max_T_value = Tvals[T_index];}
		  
		  R_index = 0;

		  /* Read in the opacity values 
		     Note: need to be able to handle stringstreams 
		     of different lengths...
		  */
		  while (ss.good() != false)
		    {
		      ss>>foo;
		      
		      /*
			Fill in the DepVars grid with the (log) kappa values.
		      */
		      double bar  = atof(foo.c_str());
		      if (bar!=9.999){ kappa[T_index][R_index] = bar;}
		      else { kappa[T_index][R_index]= ignore_flag;}

		      /*
			Fill in the IndepVars indexing grids with the locations 
		       */
		      IndepVarsGrid[T_index][R_index][0] = Tvals[T_index] ;
		      IndepVarsGrid[T_index][R_index][1] = Rvals[R_index] ;

		      // Update the R-index counter 
		      R_index++;
		    }
		  // Update the T-index counter
		  T_index++;
		}
	    }	   
	  
	}
    }
  else /* If you can't open the file with the opacity table data... */
    {
      // cout<<"Can't find the opacity table you want us to read in. \n Check the path you gave us? \n\n";
    }

  IndepVar1_min = min_T_value;
  IndepVar1_max = max_T_value;
  IndepVar2_min = min_R_value;
  IndepVar2_max = max_R_value;

  DepVarsGrid[i_kappa] = kappa;
  
}



 
//====================================================
// bundle method definitions 
//====================================================
void bundle::read_in_vars(int varnum, string filename)
 {
   /*
     Varnum:
    -1 = M (mass)
     0 = P (pressure)
     1 = r (radius)
     2 = L (luminosity)
     3 = T (temperature)
   */

   vector<double> tempvec1a(jMax),tempvec2a(jMax);
   vector<double> tempvec1b(jMax),tempvec2b(jMax);
   int index=0;
   string line,foo;
   ifstream myfile(filename.c_str());
   //  stringstream ss;

   if (myfile.is_open())
     {
       while (! myfile.eof())
	 {	
	   
	   // Read in the line of data from the table file	  
	   while ( (getline(myfile,line)) && (index < jMax))
	     {
	
	       /* Skip empty lines and header lines */
	       if ((line == "")||(line.size()<8))
		 {
		   // // cout<<"Skipping over header lines \n";
		   continue;
		 }
	       else
		 {
		   // Store the values in the first storage vector
		   tempvec1a[index] = atof(line.c_str());  // Original value
		   tempvec1b[index] = pow(10.0,tempvec1a[index]); // Value translated from log<?> to ?

		   // Interpolating the mass half-steps
		   if (index == 0 )
		     {
		       tempvec2a[index] = tempvec1a[index]; // logged
		       tempvec2b[index] = tempvec1b[index]; //un-logged
		     }
		   else
		     {
		       tempvec2a[index] = 0.5 *( tempvec1a[index-1] + tempvec1a[index]); // logged
		       tempvec2b[index] = 0.5*( tempvec1b[index-1] + tempvec1b[index]); // un-logged
		     }
		   
		   index++;
		 }
	     }
	 }
     }
 
 

   // If you're reading in the mass info, do this:
   if (varnum == -1) 
     {
       // The whole-integer index values that you read in above
       // go in the second row of the mass vector
       M[0] = tempvec2a;  // Yes, this numbering _is_ foolish.
       M[1] = tempvec1a; 
       
     }
   
   // If you're reading in either temperature (0) or pressure (3)
   // info, do this:
   if ((varnum==0) || (varnum==3) )
     {
       x[varnum] = tempvec1b; // un-logged value
     }
   
   // If you're reading in either the radius or luminosity
   // info, do this:
   if ((varnum==1) ||(varnum==2) ) //radius 
     {
       x[varnum] = tempvec1a; // not log-scale in the read-in file, so leave as is
     }

 } 


//....................................................

void bundle::update_vars(bool is_the_update_xprime_based)
{
  // This method updates rho, delta, rad_grad, ad_grad, max_grad, cP, kappa, internal_energy and Enuc (well, not yet with Enuc), based on current values of x(r,P,T,L) and on the available lookup tables.
  double logP, logT, logAnswer, Answer, R, logR, T6;
  double ratio, temp, logkappa;
  double maxlogkappa = 4.9; 
  double minlogkappa = -1.5;

  for (int j=0; j < jMax; j++)
    {
      if (is_the_update_xprime_based)
	{
	  // Calculate the 'normal' (unprimed) variables
	  ratio = fabs( (x[0][j] - exp(xprime[0][j]) )/x[0][j] );
	  if (ratio > 20.*DBL_EPSILON) 
	    {
	      x[0][j] = exp(xprime[0][j]); 
	    }

	  ratio = fabs( (x[1][j] - exp(xprime[1][j]) )/x[1][j] );
	  if (ratio > 20.*DBL_EPSILON) 
	    {
	      x[1][j] = exp(xprime[1][j]); 
	    }


	  x[2][j] = Ljup * xprime[2][j]; 

	  
	  ratio = fabs( (x[3][j] - exp(xprime[3][j]) )/x[3][j] );
	  if (ratio > 20.*DBL_EPSILON) 
	    {
	      x[3][j] = exp(xprime[3][j]); 
	    }
	  

	}

      if (!is_the_update_xprime_based)
	{
	  // Calculate the prime variables
	  xprime[0][j] = log(x[0][j]);
	  xprime[1][j] = log(x[1][j]);
	  xprime[2][j] = x[2][j] / Ljup; 
	  xprime[3][j] = log(x[3][j]); 
	}
      
      

      // For use in looking things up in the EOS table...
      //      logP = log10(P[j]);
      //logT = log10(T[j]);
      logP = log10(x[0][j]); 
      logT = log10(x[3][j]); 

 
      // Look up rho in the EOS table
      logAnswer = EqnOfStateTable.bilinear_interp(logT,logP,EqnOfStateTable.i_rho);
      Answer = pow(10.0,logAnswer); 
      rho[j] = Answer;

      // Look up the internal energy (U) in the EOS table
      logAnswer = EqnOfStateTable.bilinear_interp(logT,logP,EqnOfStateTable.i_internal_energy);
      Answer = pow(10.0,logAnswer);
      internal_energy[j] = Answer;
     

      // Look up the adiabatic gradient in the EOS table
      logAnswer = EqnOfStateTable.bilinear_interp(logT,logP,EqnOfStateTable.i_ad_grad);
      //      Answer = pow(10.0,logAnswer);
      ad_grad[j] = logAnswer;
      

      // Look up delta in the EOS table
      logAnswer = EqnOfStateTable.bilinear_interp(logT,logP,EqnOfStateTable.i_delta);
      //      Answer = pow(10.0,logAnswer);
      Answer = -1.0*logAnswer;
      delta[j] = Answer;

      // For now, we're skipping dealing with Enuc, since we assume that's zero anyway. 
      Enuc[j] = 0.0;

      // Look up the opacity in the opacity table
      // Will want to update this later to be able to determine
      // which of the opacity tables to use for this.
      // For right now, we're going to default to using only the 
      // high temperature opacity table.
      
      // First, calculate that R value...
      
      T6 = x[3][j]/pow(10.0,6); 
      R = rho[j] / pow(T6,3.0);
      logR = log10(R);


      // Then, look up the kappa value in the table
      /*       logAnswer = HighTempKappaTable.bilinear_interp(logT,logR,HighTempKappaTable.i_kappa);
       Answer = pow(10.0,logAnswer);
       kappa[j] = Answer;
      */

      // P. Bodenheimer things this kludge below may be giving me
      // a 'greenhouse effect' in my calcs.
      // TOTALLY KLUDGING THE KAPPA CALCULATION UNTIL I CAN
      // GET MY HANDS ON AN OPACITY TABLE THAT COVERS THESE
      // TEMP/DENSITY RANGES!!!
      //            kappa[j] = 150.0; 
//            kappa[0]=pow(10.0,5.0);
//            kappa[1]=pow(10.0,4.0);
//            kappa[2]=pow(10.0,-3.0);
//      
      logkappa = ((maxlogkappa - minlogkappa)/( 0.0 - double(jMax) )) * double(j) + maxlogkappa;
      kappa[j] = pow(10.0,logkappa);
      
      // Calculate the specific heat at constant pressure from the updated values above
      Answer = x[0][j] * delta[j] / (x[3][j] * rho[j] * ad_grad[j]);
      // The equation above comes from Kippenhanh & Weigert, "Stellar Structure and Evolution", 1st edition, 1990, equation (4.21)
      cP[j] = Answer;


      // Calculate the radiative gradient from the updated values above
      // (See the notes in my lab book on 10/6/2010 regarding questions
      // and possible errors in the way I'm currently calculating this.)
      Answer=0.0;
      Answer = (3.0 / (16.0 * pi * gravG * a * c) ) * ( (kappa[j] * x[2][j] * x[0][j]) / (M[1][j]* pow(x[3][j],4.0)));
      //     double temp = x[2][j] ;
      //cout<<temp<<endl;

      rad_grad[j] = Answer;

      // Calculate the 'grad' value; i.e., whether the ad_grad or the rad_grad is bigger.
      if (rad_grad[j] > ad_grad[j])
	{
	  grad[j] = ad_grad[j];
	}
      else
	{
	  grad[j] = rad_grad[j];
	}

    }



}
