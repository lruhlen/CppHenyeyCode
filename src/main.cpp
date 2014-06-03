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

#include <iomanip>

using namespace std;


string filePath, versionNum;
int IterMax;
bool WriteOutput;

int main(int argc, char *argv[])
{


  // Setting up the base of the filename path structure to write your outputs to (for debugging in python)
  versionNum  = "None";
  WriteOutput = false;
  IterMax = 2;

  if (argc > 1) 
     {
       WriteOutput = true;
       filePath = argv[1];       
       if (argc > 2)
	 {
	   versionNum = argv[2];
	   if (argc > 3)
	     {
	       IterMax = atoi(argv[3]);
	     }
	 }
     }

  string tt = "\t";
  ostringstream convert;
  // Going to have to use the Python wrapper function that calls this entire program to check that the 
  // filepath directory exists, that the file (base) names don't already exist there (i.e., so that no overwriting 
  // of extant data occurs) and all of that other stuff.
  // // Read in the starting conditions
   bundle vars;
   cout<<"\tReading in the starting model\n";
   //   vars.read_in_vars("/Users/laurel/Desktop/Research/CppHenyeyCode/InitialConds/10MjupInput.txt");
   vars.read_in_vars("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/2013/March/March_29_2013/v2/iter_1/for_Helena_read_in.txt");
   vars.oldP = vars.P;
   vars.oldr = vars.r;
   vars.oldL = vars.L;
   vars.oldT = vars.T;
   vars.read_in_vars("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/2013/March/March_29_2013/v2/iter_20/for_Helena_read_in.txt");

   vec2d eps(jMax,iMax);

  // // Read in the EOS and opacity table info
   TableGroup eos;
   cout<<"\tReading in some big honking tables.  Be patient!\n";

   eos.rho.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/rho_table_Mar12013.txt";
   eos.cp.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/cP_table_Mar12013.txt";
   eos.delta.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/del_table_Mar12013.txt";
   eos.kappa.table_name = "/Users/laurel/Desktop/Research/CppHenyeyCode/eos_tables/kappa_table_Mar12013.txt";

   eos.rho.read_in(190,139);   cout<<"\t\tRho table done\n";
   eos.cp.read_in(190,139);   cout<<"\t\tcP table done\n";
   eos.delta.read_in(190,139);  cout<<"\t\tdelta table done\n";
   eos.kappa.read_in(190,139);  cout<<"\t\tkappa table done\n";
   cout<<"\tDone reading in the big honking tables...\n";
   vars.EOS = eos;  
   vars.eos_var_update(-1);
   
 //   // vec2d tempRatio(iMax,jMax,0);
 //   // OneD temp(4);
    vec2d G(jMax,iMax,0);
    vec3d C(jMax,iMax,iMax,0), D(jMax,iMax,iMax,0),E(jMax,iMax,iMax,0);
   
    // These are the rescaling values for the dXs.
    OneD thresh(4); 
    thresh[0] = 0.08; thresh[1] = 0.08; thresh[2] = 0.25; thresh[3] = 0.08;
    //    thresh[0] = 0.06; thresh[1] = 0.06; thresh[2] = 0.5; thresh[3] = 0.06;
    //    thresh[0] = 0.1; thresh[1] = 0.1; thresh[2] = 0.1; thresh[3] = 0.1;
    int IsModelConverged = 0;
    vec2d temp(iMax,jMax,0);


  // The convergence loop starts here...
    for (int i=1;i<IterMax; i++)
     {
        cout<<"\n\n----------------------------\n";
        cout<<"On convergence loop #"<<i<<endl;

	// Reset IsModelConverged value
	IsModelConverged = 0;
	convert.str("");
	//	convert.clear();
	convert << i;


	// Calculate the CDEG matrices
	cout<<"CDEG value calcs...\n";
	NewCalcCDEG(vars, G, C, D, E);
    
       if (WriteOutput)
  	{ 
  	  cout<<"\tWriting CDEG values to file\n";
	  // Open files for writing the CDEG outputs to.
  	  ofstream Goutput, Coutput, Doutput, Eoutput;
  	  string tempName;
 	  
  	  tempName = filePath + "_G_debug_v" + versionNum  + "_iter_" + convert.str() + ".txt";
  	  Goutput.open(tempName.c_str());

  	  tempName = filePath + "_C_debug_v" + versionNum  + "_iter_" + convert.str() + ".txt";
  	  Coutput.open(tempName.c_str());

  	  tempName = filePath + "_D_debug_v" + versionNum  + "_iter_" + convert.str() + ".txt";
  	  Doutput.open(tempName.c_str());
 	  
  	  tempName = filePath + "_E_debug_v" + versionNum  + "_iter_" + convert.str() + ".txt";
  	  Eoutput.open(tempName.c_str());

  	  Goutput<<"MassCellNumber\tG1\tG2\tG3\tG4\n";
  	  Coutput<<"j\tC11\tC12\tC13\tC14\tC21\tC22\tC23\tC24\tC31\tC32\tC33\tC34\tC41\tC42\tC43\tC44\n";
  	  Doutput<<"j\tD11\tD12\tD13\tD14\tD21\tD22\tD23\tD24\tD31\tD32\tD33\tD34\tD41\tD42\tD43\tD44\n";
  	  Eoutput<<"j\tE11\tE12\tE13\tE14\tE21\tE22\tE23\tE24\tE31\tE32\tE33\tE34\tE41\tE42\tE43\tE44\n";
 	  
	  Goutput.precision(15); 	  
	  Coutput.precision(15);
	  Doutput.precision(15);
	  Eoutput.precision(15);


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
       cout<<"Solving for dX corrections...\n";
       modifiedHenyeyMatrixInversion(vars,C,D,E,G,convert.str());

       /*
	 Rescale the corrections 
       */ 	              
        cout<<"Rescaling the corrections...\n";
	temp[0] = vars.dP;
	temp[1] = vars.dr;
	temp[2] = vars.dL;
	temp[3] = vars.dT;


        for (int j=0; j<jMax; j++)
	  { 	  
	    if (fabs(vars.dP[j]/vars.P[j]) > thresh[0])
	      {
		vars.dP[j] = thresh[0] * (vars.dP[j] * vars.P[j]/fabs(vars.dP[j]));
		//        	       IsModelConverged++;
	      }
	    if (fabs(vars.dr[j]/vars.r[j]) > thresh[1])
	      {
		vars.dr[j] = thresh[1] * (vars.dr[j]/fabs(vars.dr[j])) * vars.r[j];
		//        	       IsModelConverged++;
	      }
	     if (fabs(vars.dL[j]/vars.L[j]) > thresh[2])
	       {
	     	vars.dL[j] = thresh[2] * (vars.dL[j]/fabs(vars.dL[j])) * vars.L[j];
	     	//        	        IsModelConverged++;
	       }
	    if (fabs(vars.dT[j]/vars.T[j]) > thresh[3])
	      {
		vars.dT[j] = thresh[3] * (vars.dT[j]/fabs(vars.dT[j])) * vars.T[j];
		//        	       IsModelConverged++;
	      } 
	    
	    eps[j][0] = 2.0*vars.dP[j] / (vars.P[j]+vars.dP[j]+vars.oldP[j]);
	    eps[j][1] = 2.0*vars.dr[j] / (vars.r[j]+vars.dr[j]+vars.oldr[j]);
	    eps[j][2] = 2.0*vars.dL[j] / (vars.L[j]+vars.dL[j]+vars.oldL[j]);
	    eps[j][3] = 2.0*vars.dT[j] / (vars.T[j]+vars.dT[j]+vars.oldT[j]);
	    
	  }
	//        cout<<"\tModel is this far from convergence: "<<IsModelConverged<<endl;

  
 
       // // Apply the corrections
       cout<<"Applying corrections...\n";
       vars.P = addMatrix(vars.dP,vars.P);
       vars.r = addMatrix(vars.dr,vars.r);
       vars.L = addMatrix(vars.dL,vars.L);
       vars.T = addMatrix(vars.dT,vars.T);


       cout<<setprecision(14)<<vars.P[0]<<tt<<vars.r[0]<<tt<<vars.L[0]<<tt<<vars.T[0]<<endl;
       cout<<vars.oldP[0]<<tt<<vars.oldr[0]<<tt<<vars.oldL[0]<<tt<<vars.oldT[0]<<endl;
       cout<<vars.dP[0]<<tt<<vars.dr[0]<<tt<<vars.dL[0]<<tt<<vars.dT[0]<<endl;
       printMatrix(eps[0]);
       cout<<endl;


       if (WriteOutput)
  	{
  	  ofstream dXoutput;
  	  string tempName = filePath + "_dX_debug_v" + versionNum + "_iter_" + convert.str() + ".txt";
  	  dXoutput.open(tempName.c_str());
	  dXoutput.precision(15);
	  dXoutput<<"J\tdP\tdPrescaled\tdr\tdrrescaled\tdL\tdLrescaled\tdT\tdTrescaled\t P\t r\t L\t T\t M\tdM\trho"<<endl;
	  for (int j=0; j<jMax; j++)
	    {
	      dXoutput<<j<<tt<<temp[0][j]<<tt<<vars.dP[j]<<tt<<temp[1][j]<<tt<<vars.dr[j]<<tt<<temp[2][j]<<tt<<vars.dL[j]<<tt<<temp[3][j]<<tt<<vars.dT[j]<<tt<<vars.P[j]<<tt<<vars.r[j]<<tt<<vars.L[j]<<tt<<vars.T[j]<<tt<<vars.Mwhole[j]<<tt<<vars.dMwhole[j]<<tt<<vars.rho[j]<<endl;	   
	    }
	  dXoutput.close();
	}
   
     } 
   
   cout<<"\nDone with the iteration loops.\n\n";
   return 0;
} 
