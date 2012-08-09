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
#include "matrixDivide.h"
#include "matrixInvert.h"
#include "FindNonZeroMax.h"
#include "cleanMatrix.h"
#include "G1J.h"
#include "G2J.h"
#include "G3J.h"
#include "G4J.h"
#include "NewCalcCDEG.h"
#include "modifiedHenyeyMatrixInversion.h"
#include "pause_for_user.h"
#include "atmos.h"
#include "ReadInArray.h"
#include "fourbyfourinvert.h"
using namespace std;


int main()
{

  // // Read in the starting conditions
   bundle vars;
  // // Read in the EOS and opacity table info
   TableGroup eos;

   // //  Read in the kludgy low-temperature & low-pressure eos table
   // //  Remember: in these tables xvals = log10(P), yvals = log10(T)
   // //   eos.rho.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/rho1000.txt";
   // eos.rho.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/rho_for_n32_1Msun.txt";
   // eos.rho.read_in(1000,1000);  
   // //   eos.cp.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/cP1000.txt";
   // eos.cp.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/cP_for_n32_1Msun.txt";
   // eos.cp.read_in(1000,1000);  
   // //   eos.delta.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/delta1000.txt";
   // eos.delta.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/delta_for_n32_1Msun.txt";
   // eos.delta.read_in(1000,1000);  
   // //   eos.kappa.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/opacity_tables/kappa1000.txt";
   // eos.kappa.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/kappa_for_n32_1Msun.txt";
   // eos.kappa.read_in(1000,1000);   
   // //   cout<<"\nDone reading in eos tables\n";
   // vars.EOS = eos;  
   // //   cout<<"\nDone setting the vars eos tables\n";
  
     //   vars.read_in_vars("/Users/laurel/Desktop/Research/CppHenyeyCode/InitialConds/n32_1Msun_init_model.txt");
   //   vars.read_in_vars("/Users/laurel/Desktop/Research/CppHenyeyCode/InitialConds/10MjupInput.txt");
   vars.read_in_vars("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/cdeg_var_vals.txt");
   //   cout<<"\nDone reading in vars\n";

   //   vars.eos_var_update(-1);
   //   cout<<"\nDone setting the lookup/update eos vars!\n";

   vec2d tempRatio(iMax,jMax,0);
   OneD temp(4);
   vec2d G(jMax,iMax,0);
   vec3d C(jMax,iMax,iMax,0), D(jMax,iMax,iMax,0),E(jMax,iMax,iMax,0);
   double PratioMax, RratioMax, LratioMax, TratioMax;
   double rescale;
   OneD thresh(4); thresh[0] = 0.06; thresh[1] = 0.06; thresh[2] = 0.5; thresh[3] = 0.06;
   
   C = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/c_values.txt",jMax,iMax,iMax);
   D = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/d_values.txt",jMax,iMax,iMax);
   E = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/e_values.txt",jMax,iMax,iMax);
   G = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/g_values.txt",jMax,iMax);

   // temp = atmos(vars.r[jMax-1], vars.L[jMax-1], vars.dMwhole[jMax-1], vars.Mwhole[jMax-1], vars.EOS);
   // //       cout<<"\nDone running the atmos subroutine!\n";
   
   // // Reset the outer P/T/rho values accordingly
   // vars.P[jMax-1] = temp[2];
   // vars.T[jMax-1] = temp[3];
   // vars.rho[jMax-1] = temp[4];
   
   
  // The convergence loop starts here...
   for (int i=1;i<2; i++)
     {
       // cout<<"\n\n----------------------------\n";
       // cout<<"On convergence loop #"<<i<<endl;
    
       // Calculate the CDEG matrices
       //       NewCalcCDEG(vars, G, C, D, E);
       //       cout<<"\nDone running the NewCalcCDEG subroutine!\n";


       // Run the Henyey matrix inversion & correction finder subroutine
       modifiedHenyeyMatrixInversion(vars,C,D,E,G);
       //       cout<<"\nDone running the Henyey Matrix inversion subroutine!\n";

       // tempRatio[0] = matrixDivide(vars.dP,vars.P);
       // tempRatio[1] = matrixDivide(vars.dr,vars.r);
       // tempRatio[2] = matrixDivide(vars.dL,vars.L);
       // tempRatio[3] = matrixDivide(vars.dT,vars.T);
       // cout<<FindNonZeroMax(tempRatio[0])<<"\t"<<FindNonZeroMax(tempRatio[1])<<"\t"<<FindNonZeroMax(tempRatio[2])<<"\t"<<FindNonZeroMax(tempRatio[3])<<endl;
       // cout<<"Max dX/X = "<<FindNonZeroMax(tempRatio)<<endl;
  /*
    Rescale the corrections 
   */
       cout<<"MassCellNumber	 dP	 dr	 dL	 dT	 dPrescaled	 drrescaled	 dLrescaled	 dTrescaled	 P	 r	 L	 T"<<endl;
       for (int j=0; j<jMax; j++)
	 {
	   cout<<j<<"  "<<vars.dP[j]<<"  "<<vars.dr[j]<<"  "<<vars.dL[j]<<"  "<<vars.dT[j]<<"  ";

	   if (fabs(vars.dP[j]/vars.P[j]) > thresh[0])
	     {
	       vars.dP[j] = thresh[0] * (vars.dP[j] * vars.P[j]/fabs(vars.dP[j]));
	     }
	   if (fabs(vars.dr[j]/vars.r[j]) > thresh[1])
	     {
	       vars.dr[j] = thresh[1] * (vars.dr[j]/fabs(vars.dr[j])) * vars.r[j];
	     }
	   if (fabs(vars.dL[j]/vars.L[j]) > thresh[2])
	     {
	       vars.dL[j] = thresh[2] * (vars.dL[j]/fabs(vars.dL[j])) * vars.L[j];
	     }
	   if (fabs(vars.dT[j]/vars.T[j]) > thresh[3])
	     {
	       vars.dT[j] = thresh[3] * (vars.dT[j]/fabs(vars.dT[j])) * vars.T[j];
	     }      
	   cout<<vars.dP[j]<<"  "<<vars.dr[j]<<"  "<<vars.dL[j]<<"  "<<vars.dT[j]<<"  ";
	   cout<<vars.P[j]<<"  "<<vars.r[j]<<"  "<<vars.L[j]<<"  "<<vars.T[j]<<endl;

	 }

       // Apply the corrections
       vars.P = addMatrix(vars.dP,vars.P);
       vars.r = addMatrix(vars.dr,vars.r);
       vars.L = addMatrix(vars.dL,vars.L);
       vars.T = addMatrix(vars.dT,vars.T);
       //       cout<<"\nFinished applying the corrections\n";
     }
 
   //  cout<<"\nDone!\n";
   
  return 0;
} 
