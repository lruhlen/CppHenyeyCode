#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>
#include <float.h>
#include "global.h"
#include "AboutThisRun.h"
#include "matrixDivide.h"

void plot_bundle(bundle &vars, FILE *gp)
{

  // Fill the data files that gnuplot will use
  ofstream tempoutfile1,tempoutfile2;
  string tempoutfile1name, tempoutfile2name;
  tempoutfile1name = "temp";
  tempoutfile1.open(tempoutfile1name.c_str());

  vec2d ratio(iMax,jMax);
  ratio = matrixDivide(vars.dxprime,vars.xprime);
		    
  for (int j=0; j<jMax; j++) 
    {
      // mass, pressure, radius, luminosity, temperature
      tempoutfile1<<vars.M[0][j]<<"\t"<<vars.rho[j]<<"\t"<<vars.x[0][j]<<"\t"<<vars.x[1][j]<<"\t" <<vars.x[2][j]<<"\t" <<vars.x[3][j]<<endl;
    }
  
  tempoutfile1.close();
  
  // Submit the plotting commands to gnuplot
  fprintf(gp,"unset key \n");
  //  fprintf(gp, "set logscale xy \n");
  //  fprintf(gp, "set pointsize 1.0\n");
  fprintf(gp,"set style line 1 lt 3 lw 3 \n");

  fprintf(gp,"set xlabel \"Mass Bin Number\" \n");
  fprintf(gp,"set ylabel \"Density (g/cm^3) \" \n");
  fprintf(gp,"set yrange [0:10] \n");

  fprintf(gp,"plot \"%s\" using 2 with linespoints linestyle 1\n",tempoutfile1name.c_str()); 


  //  fprintf(gp,"set multiplot\n");
  //		 fprintf(gp,"set xlabel \"Radius (cm)\"  \n"); 
  //fprintf(gp,"set size 0.46,0.46\n");
  
  /*  // plot mass vs. radius
  fprintf(gp,"set origin 0,0\n");
  //		 fprintf(gp,"set xrange [10**8:10**10]\n");
  // fprintf(gp,"set logscale xy\n"); 
  fprintf(gp,"set pointsize 1.2\n");
  fprintf(gp,"set title \" Mass vs. dR/R \" 0.0,-5.0\n ");
  //fprintf(gp,"set xlabel \"Mass (g)\", 0.0,5.0\n");
  fprintf(gp,"plot \"%s\" using 1:3 3\n",tempoutfile1name.c_str()); 
  
  
  // plot pressure vs. radius
  fprintf(gp,"unset xlabel\n");
  fprintf(gp,"set origin 0,0.5\n");
  //		 fprintf(gp,"set xrange [10**8:10**10]\n");
  //		 fprintf(gp,"set logscale xy\n"); 
  fprintf(gp,"set pointsize 1.2\n");
  fprintf(gp,"set title \" Mass vs. dP/P \" \n ");
  fprintf(gp,"plot \"%s\" using 1:2 2\n",tempoutfile1name.c_str()); 
  
  
  // plot luminosity vs. radius
  fprintf(gp,"unset xlabel\n");
  fprintf(gp,"set origin 0.5,0.0\n");
  //		 fprintf(gp,"set xrange [10**8:10**10]\n");
  //		 fprintf(gp,"set logscale xy\n"); 
  fprintf(gp,"set pointsize 1.2\n");
  fprintf(gp,"set title \" Mass vs. dL/L \"  \n ");
  fprintf(gp,"plot \"%s\" using 1:4 4\n",tempoutfile1name.c_str()); 
  
  
  // plot temperature vs. radius
  fprintf(gp,"unset xlabel\n");
  fprintf(gp,"set origin 0.5,0.5\n");
  //		 fprintf(gp,"set xrange [10**8:10**10]\n");
  //	 fprintf(gp,"set logscale xy\n"); 
  fprintf(gp,"set pointsize 1.2\n");
  fprintf(gp,"set title \" Mass vs. dT/T \"  \n ");
  fprintf(gp,"plot \"%s\" using 1:5 5\n",tempoutfile1name.c_str()); 
  */
  

  // Print the result to a .ps file...
  fprintf(gp,"set term postscript\n");
  fprintf(gp,"set output \"printme.ps\"\n"); 
  fprintf(gp,"replot \n");
  fprintf(gp,"set term x11\n");

  fflush(gp); 
		    


}
