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
#include "NewCalcCDEG_flip.h"
#include "modifiedHenyeyMatrixInversion.h"
#include "pause_for_user.h"
#include "atmos.h"
#include "ReadInArray.h"
#include "fourbyfourinvert.h"
using namespace std;


string filePath, versionNum;
bool WriteOutput;

int main(int argc, char *argv[])
{


  // Setting up the base of the filename path structure to write your outputs to (for debugging in python)
  versionNum  = "None";
  WriteOutput = false;

  if (argc > 1) 
     {
       WriteOutput = true;
       filePath = argv[1];       
       if (argc > 2)
	 {
	   versionNum = argv[2];
	 }
     }


  // Going to have to use the Python wrapper function that calls this entire program to check that the 
  // filepath directory exists, that the file (base) names don't already exist there (i.e., so that no overwriting 
  // of extant data occurs) and all of that other stuff.


  // // Read in the starting conditions
   bundle vars;
  // // Read in the EOS and opacity table info
   TableGroup eos;

   //  Read in the kludgy low-temperature & low-pressure eos table
   //  Remember: in these tables xvals = log10(P), yvals = log10(T)
   eos.rho.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/bigger_rho.txt";
   eos.rho.read_in(1000,1000);  

   eos.cp.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/bigger_cP.txt";
   eos.cp.read_in(1000,1000);  

   eos.delta.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/bigger_del.txt";
   eos.delta.read_in(1000,1000);  

   eos.kappa.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/bigger_kappa.txt";
   eos.kappa.read_in(1000,1000);   
   vars.EOS = eos;  
   
   vars.read_in_vars("/Users/laurel/Desktop/Research/CppHenyeyCode/InitialConds/10MjupInput.txt");

   cout<<"M[last] = "<<vars.Mwhole[jMax-1]<<endl;
   cout<<"P[last] = "<<vars.P[jMax-1]<<endl;
   cout<<"R[last] = "<<vars.r[jMax-1]<<endl;
   cout<<"L[last] = "<<vars.L[jMax-1]<<endl;
   cout<<"T[last] = "<<vars.T[jMax-1]<<endl;
   vars.eos_var_update(-1);
   
   // vec2d tempRatio(iMax,jMax,0);
   // OneD temp(4);
   vec2d G(jMax,iMax,0);
   vec3d C(jMax,iMax,iMax,0), D(jMax,iMax,iMax,0),E(jMax,iMax,iMax,0);
   
   // double rescale;
   OneD thresh(4); thresh[0] = 0.06; thresh[1] = 0.06; thresh[2] = 0.5; thresh[3] = 0.06;
   
    // double Rtemp, Mtemp, Lout, dMtemp;
    // Rtemp = 87542104809.4471 ;
    // Mtemp = 1.74866368e+31;
    // Lout = 1.402235808868283e+32;
    // dMtemp = 6.661375655694928e+28;
   
    
    //   atmos(Rtemp, Lout, dMtemp, Mtemp, vars.EOS);

   // vec3d PeterC(jMax,iMax,iMax), PeterD(jMax,iMax,iMax), PeterE(jMax,iMax,iMax);
   // vec2d PeterG(jMax,iMax);
   
  //  if (false)
  //    {
  //      PeterC = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/10MjNF_cvalues.txt",jMax,iMax,iMax);
  //      PeterD = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/10MjNF_dvalues.txt",jMax,iMax,iMax);
  //      PeterE = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/10MjNF_evalues.txt",jMax,iMax,iMax);
  //      PeterG = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/10MjNF_gvalues.txt",jMax,iMax);

  //      //        PeterC = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/c_values.txt",jMax,iMax,iMax);
  // 	//	PeterC = matrixMultiply(-1.0,PeterC);
  //      //        PeterD = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/d_values.txt",jMax,iMax,iMax);
  // 	//	PeterD = matrixMultiply(-1.0,PeterD);
  //      //        PeterE = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/e_values.txt",jMax,iMax,iMax);
  // 	//	PeterE = matrixMultiply(-1.0,PeterE);
  //      //        PeterG = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/g_values.txt",jMax,iMax);
  //    }
   

 // The convergence loop starts here...
  for (int i=1;i<2; i++)
    {
       cout<<"\n\n----------------------------\n";
       cout<<"On convergence loop #"<<i<<endl;

      // Calculate the CDEG matrices
      NewCalcCDEG(vars, G, C, D, E);
      
      if (WriteOutput)
	{ 
	  // Open files for writing the CDEG outputs to.
	  ofstream Goutput, Coutput, Doutput, Eoutput;
	  string tempName;
	  
	  tempName = filePath + "_G_debug_v" + versionNum + ".txt";
	  Goutput.open(tempName.c_str());
	  
	  tempName = filePath + "_C_debug_v" + versionNum + ".txt";
	  Coutput.open(tempName.c_str());
	  
	  tempName = filePath + "_D_debug_v" + versionNum + ".txt";
	  Doutput.open(tempName.c_str());
	  
	  tempName = filePath + "_E_debug_v" + versionNum + ".txt";
	  Eoutput.open(tempName.c_str());
	  
	  Goutput<<"MassCellNumber\tG1\tG2\tG3\tG4\n";
	  Coutput<<"j\tC11\tC12\tC13\tC14\tC21\tC22\tC23\tC24\tC31\tC32\tC33\tC34\tC41\tC42\tC43\tC44\n";
	  Doutput<<"j\tD11\tD12\tD13\tD14\tD21\tD22\tD23\tD24\tD31\tD32\tD33\tD34\tD41\tD42\tD43\tD44\n";
	  Eoutput<<"j\tE11\tE12\tE13\tE14\tE21\tE22\tE23\tE24\tE31\tE32\tE33\tE34\tE41\tE42\tE43\tE44\n";
	  
	  for(int j=0; j<jMax; j++)
	    {
	      Goutput<<j+1<<"\t";
	      Coutput<<j+1<<"\t";
	      Doutput<<j+1<<"\t";
	      Eoutput<<j+1<<"\t";
	      
	      for(int row=0; row<iMax; row++)
		{
		  Goutput<<G[j][row]<<"\t";
		  
		  for(int col=0; col<iMax; col++)
		    {
		      Coutput<<C[j][row][col]<<"\t";
		      Doutput<<D[j][row][col]<<"\t";
		      Eoutput<<E[j][row][col]<<"\t";
		    }
		}
	      Goutput<<endl;
	      Coutput<<endl;
	      Doutput<<endl;
	      Eoutput<<endl;
	    }
	  Goutput.close();
	  Coutput.close();
	  Doutput.close();
	  Eoutput.close();
	}
      
      
      // // Run the Henyey matrix inversion & correction finder subroutine
      modifiedHenyeyMatrixInversion(vars,C,D,E,G);
      
      if (WriteOutput)
	{
	  ofstream dXoutput;
	  string tempName = filePath + "_dX_debug_v" + versionNum + ".txt";
	  dXoutput.open(tempName.c_str());
	  
	  /*
	    Rescale the corrections 
	  */
 	   dXoutput<<"MassCellNumber	 dP	 dr	 dL	 dT	 dPrescaled	 drrescaled	 dLrescaled	 dTrescaled	 P	 r	 L	 T"<<endl;
 	   for (int j=0; j<jMax; j++)
 	     {
 	       dXoutput<<j<<"  "<<vars.dP[j]<<"  "<<vars.dr[j]<<"  "<<vars.dL[j]<<"  "<<vars.dT[j]<<"  ";
	       
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
 	       dXoutput<<vars.dP[j]<<"  "<<vars.dr[j]<<"  "<<vars.dL[j]<<"  "<<vars.dT[j]<<"  ";
 	       dXoutput<<vars.P[j]<<"  "<<vars.r[j]<<"  "<<vars.L[j]<<"  "<<vars.T[j]<<endl;
 	     }
 	   dXoutput.close();
	}
   
      // //       // // Apply the corrections
      // //       // vars.P = addMatrix(vars.dP,vars.P);
      // //       // vars.r = addMatrix(vars.dr,vars.r);
      // //       // vars.L = addMatrix(vars.dL,vars.L);
      // //       // vars.T = addMatrix(vars.dT,vars.T);
    } 

  return 0;
} 
