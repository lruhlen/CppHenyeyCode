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
#include "flattenMatrix.h"
#include "unflattenMatrix.h"
#include "matrixTranspose.h"
#include "dotProduct.h"
#include "addMatrix.h"
#include "subtractMatrix.h"
#include "matrixMultiply.h"
#include "matrixDivide.h"
#include "matrixExtract.h"
#include "matrixImplant.h"
#include "FindInMatrix.h"
#include "convert_to_vec2d.h"
#include "convert_from_vec2d.h"
#include "FindMax.h"
#include "FindNonZeroMax.h"
#include "FindMin.h"
#include "FindNonZeroMin.h"
#include "matrixInvert.h"
#include "cleanMatrix.h"
#include "printMatrixToFile.h"

#include "PartialDeriv.h"

#include "G1Jprime.h"
#include "G2Jprime.h"
#include "G3Jprime.h"
#include "G4Jprime.h"

#include "CalcCDEGprime.h"
#include "HenyeyPrimeMatrixInversion.h"
#include "MakeHenyeyMatrix.h"

#include "pause_for_user.h"
#include "plot_bundle.h"

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
  bool PlotToScreen = false;
  bool use_xprime = true;
  bool use_x = false;

  double rescaleFactor, initial_error, error;
  double Pscale, Tscale;
  string continueHit;
  
  int size = iMax*jMax;
  OneD flatG(size,0.0),temp;

  vec2d ratio(iMax,jMax);
  vec2d HenyeyMatrix(jMax,jMax), InverseHenyeyMatrix(jMax,jMax);  
  vec2d G(iMax,jMax), Gprime(iMax,jMax);
  vec3d C(iMax,iMax,jMax),D(iMax,iMax,jMax),E(iMax,iMax,jMax);
  vec3d Cprime(iMax,iMax,jMax), Dprime(iMax,iMax,jMax), Eprime(iMax,iMax,jMax);

  bundle vars, initial_vars;
  vars.M = vec2d(2,jMax,1.0);
  vars.x = vec2d(iMax,jMax,1.0);  
  vars.dx = vec2d(iMax,jMax,0.0);
  vars.x_old = vec2d(iMax,jMax,0.0);
  vars.dx_old = vec2d(iMax,jMax,0.0);

  vars.xprime = vec2d(iMax,jMax,0.0);
  vars.dxprime = vec2d(iMax,jMax,0.0); 
  vars.xprime_old = vec2d(iMax,jMax,0.0); 
  vars.dxprime_old = vec2d(iMax,jMax,0.0); 
 
  vars.rho = vector<double>(jMax,1.0);
  vars.rad_grad = vector<double>(jMax,1.0);
  vars.ad_grad = vector<double>(jMax,1.0);
  vars.grad = vector<double>(jMax,1.0); 
  vars.delta = vector<double>(jMax,1.0);
  vars.cP = vector<double>(jMax,1.0);
  vars.kappa = vector<double>(jMax,1.0);
  vars.Enuc = vector<double>(jMax,1.0);
  vars.internal_energy = vector<double>(jMax,1.0);

  //  vars.EqnOfStateTable.table_name = "/home/grads/laurel/Desktop/PlanetsResearch/HenyeyCode/eos_tables/H_TAB_I.A";
  //  vars.HighTempKappaTable.table_name = "/home/grads/laurel/Desktop/PlanetsResearch/HenyeyCode/opacity_tables/small-test-opacity-table.txt";
    
  vars.EqnOfStateTable.table_name = eos_table;
  vars.HighTempKappaTable.table_name = opacity_table;

    //#######################################
    // Initialize variables
    //#######################################
  vars.read_in_vars(-1,M_initial_conds);
  // And then renormalize them to the actual jupiter mass
  vars.M = matrixMultiply(Mjup,vars.M);

    
  // Read in the initial Radius, Temperature, and Pressure values
  vars.read_in_vars(0,P_initial_conds);

  vars.read_in_vars(1,r_initial_conds);
  vars.x[1] = matrixMultiply(Rjup,vars.x[1]);
    
  vars.read_in_vars(2,L_initial_conds);
  vars.x[2] = matrixMultiply(Ljup,vars.x[2]);
 
  vars.read_in_vars(3,T_initial_conds);  

 
  // Read in values to the EOS lookup table
  vars.EqnOfStateTable.read_in();
  
  // Read in values to the opacity lookup table
  vars.HighTempKappaTable.read_in();
 
  // Fill in the rho, rad_grad, ad_grad, delta and kappa
  // by using the initial conds we just read in to interpolate
  // these quantities from their respective tables.
  vars.update_vars(use_x);


  // A kludge, for now:
  vars.x_old[0] = matrixMultiply(1.0-pow(10.0,-9.0),vars.x[0]);
  vars.x_old[3] = matrixMultiply(1.0-pow(10.0,-6.0),vars.x[3]);

  // Initialize vars.x_old for the first pass through the 
  // time-steps loop

  /*+++++++++++++++++++++++++++++++++++++
    Set up screen plotting, if you want to
    do that.
    +++++++++++++++++++++++++++++++++++++*/
  FILE *gp;
  gp = popen("gnuplot -persist -geometry 300x300","w");
  


  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ 
  //End of:
  // Setting things up
  //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  //START OF
  // LOOP 1: LOOP OVER TIME STEPS
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  
  double t = 0.0;
  

	   
  //+++++++++++++++++++++++++++++++++++++++
  // Update the bundle of vars to reflect
  // this new timestep
  //+++++++++++++++++++++++++++++++++++++++

      //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      //START OF
      // LOOP 2: SPATIAL SOLN. CONVERGENCE
      //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  error = 10 * tolerance;
  int conv_loop_num = 1; 
  
  while (fabs(error) > tolerance) 
    //while (conv_loop_num < 1)
    {
      
      //+++++++++++++++++++++++++++++++++++++++ 
      // If unconverged, replace x_j's by
      // x_j + dx_j's, and repeat loop
      //+++++++++++++++++++++++++++++++++++++++
      vars.xprime = addMatrix(vars.xprime,vars.dxprime);
      
      //+++++++++++++++++++++++++++++++++++++++
      // Also, update all of the internal info in vars
      // (density, cP, internal energy, etc.) to
      // reflect the new P/T/r/L values.
      //+++++++++++++++++++++++++++++++++++++++
      vars.update_vars(use_xprime); 
      
      
      //+++++++++++++++++++++++++++++++++++++++
      // Numerically calculate the components
      // of G, C, D, and E
      //+++++++++++++++++++++++++++++++++++++++
      CalcCDEGprime(vars, Cprime, Dprime, Eprime, Gprime);

      //+++++++++++++++++++++++++++++++++++++++
      // Invert the large matrix
      //+++++++++++++++++++++++++++++++++++++++
      
      HenyeyPrimeMatrixInversion(vars,Cprime,Dprime,Eprime,Gprime);
      
 	   
      // Calculate the error/tolerance measure here.
      ratio = matrixDivide(vars.dxprime,vars.xprime);
      error = fabs(FindNonZeroMax(ratio));

      // Various debugging statements...
      if (debugflag >= 1)
	{ 	   
	  cout<<"\tLoop number "<<conv_loop_num<<endl; 
	  cout<<"Current error is: "<<error<<endl;
	}

      if (debugflag >= 3)
	{ 	   
	  cout<<"\n\t\t\t......................................\n";
	  cout<<"\t \t \t The xprimes:\n";
	  printMatrix(vars.xprime[0]); cout<<endl;
	  printMatrix(vars.xprime[1]); cout<<endl;
	  printMatrix(vars.xprime[2]); cout<<endl;
	  printMatrix(vars.xprime[3]); cout<<endl;
	  cout<<"\t\t\t......................................\n";
	}

      if (debugflag >= 3)
	{ 	   
	  cout<<"\n\t\t\t......................................\n";
	  cout<<"\t \t \t dxprimes:\n";
	  cout<<"\t\t\t......................................\n";
	  printMatrix(vars.dxprime[0]); cout<<endl;
	  printMatrix(vars.dxprime[1]); cout<<endl;
	  printMatrix(vars.dxprime[2]); cout<<endl;
	  printMatrix(vars.dxprime[3]); cout<<endl;
	  
	  cout<<"\t\t\t......................................\n";
	}

       if (debugflag >= 3)
	{ 	   
	  cout<<"\n\t\t\t......................................\n";
	  cout<<"\t \t \t The ratios of dxprime/xprime are:\n";
	  cout<<"\t\t\t......................................\n";
	  printMatrix(ratio);
	  cout<<"\t\t\t......................................\n";
	}
       if (debugflag >=3)
	 {
	   cout<<"ad_grad list:\n"; 
	   printMatrix(vars.ad_grad);
	   cout<<"\n rad_grad list:\n";
	   printMatrix(vars.rad_grad);
	 }
       if (debugflag >=3)
	 {
	   cout<<"\nConvection or radiation?\n";
	   for (int j=0; j<jMax; j++)
	     { 
	       if (vars.grad[j] == vars.ad_grad[j])
		 {
		   cout<<"Con: "<<vars.ad_grad[j]<<" ";
		 }
	       else
		 {
		   cout<<"Rad: "<<vars.rad_grad[j]<<" ";
		 }
	     }
	   cout<<endl;
	 }
     
      
      // Calculate the necessary re-scaling factor for the dxprimes
      if (fabs(error) < 0.1)
	{
	  rescaleFactor = 0.1; 
	}
      else
	{
	  rescaleFactor = 0.1/error;
	}
      
      // Re-scale the dxprimes
      vars.dxprime = matrixMultiply(rescaleFactor,vars.dxprime);
	   
      if (fabs(error) < 500.00)
	{   
	  FILE *outfile;
	  outfile = fopen("/home/grads/laurel/Desktop/PlanetsResearch/TestCalcsInIDL/densities_after_several_loops.txt","w");

	  fprintf(outfile,"Density after %i loops:\n",conv_loop_num);
	  printMatrixToFile(outfile,vars.rho);
	  fclose(outfile);

	}
		
      /*+++++++++++++++++++++++++++++++++++++
	Execute the screen plotting commands, 
	if you want to do that.
	+++++++++++++++++++++++++++++++++++++*/
      
      //      if (PlotToScreen && (conv_loop_num %1 ==0))
	  plot_bundle(vars,gp);
	  //	}
      
      
      //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      //END OF
      // LOOP 2: SPATIAL SOLN. CONVERGENCE
      //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      
      conv_loop_num++;
      // "clears" the screen
      cout << string(20, '\n');

      
    }
  
  
  //#######################################
  // Write the output (P,L,r,T as functs 
  // of M) to output file(s)
  //#######################################
  
  // Code this in here at some point...
  
  
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  //END OF
  // LOOP 1: LOOP OVER TIME STEPS
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  /*       vars.xprime_old = vars.xprime;
	   vars.dxprime_old = vars.dxprime;
	   
	   t += delta_t;
  */
  
  //#######################################
  // DONE!
  //#######################################
  pclose(gp);
   cout<<"\nDone!"<<endl;
  return 0;
}



 
