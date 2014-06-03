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
#include "pause_for_user.h"
#include <algorithm>
using namespace std;
//====================================================
// Table method definitions
//====================================================

void Table::read_in(int numXvals, int numYvals)
{
  // First line in the table is the x-values
  // Second line in the table is the y-values
  // The remaining data are the grid values

  // Open the file and read in its contents
  ifstream myfile(table_name.c_str());
  stringstream ss;
  int linenum = 0;
  string line, foo;
  OneD tempxvals(numXvals,0), tempyvals(numYvals,0);
  vec2d tempgridvals(numYvals,numXvals,0);

  
  if (myfile.is_open())
    { 
      while(! myfile.eof())
	{ 
	  getline(myfile,line);
	  ss.clear();
	  ss.str(line);
	  ss >> ws;
	  

	  if (line.find("//") != string::npos) // skip over comments in the input file
	    {
	      continue;
	    }

	  if (linenum==0) //read in the x-vals
	    { 
	      for (int word = 0; word < numXvals; word++)
		{
		  ss >> foo;	
		  tempxvals[word] = atof(foo.c_str());	
		}
	    }
	      
	  else if (linenum==1) //read in the y-vals
	    { 
	      for (int word = 0; word < numYvals; word++)
		{
		  ss >> foo;		  
		  tempyvals[word] = atof(foo.c_str());	
		}
	    }
	  
	  else if (linenum -2 < numYvals)
	    { 
	      // read in the grid values
	      for (int word = 0; word < numXvals; word++)
		{
		  ss >> foo;
		  tempgridvals[linenum-2][word] =  atof(foo.c_str());
		}
	    }
	
	  linenum++;	  
	}
    }
  else
    {
      cout<<"ERROR: Can't open the file: "<<table_name<<endl;
      exit(1);
    }
  xvals = tempxvals;
  yvals = tempyvals;
  gridvals = tempgridvals;

}

void Table::printTable()
{
  cout<<"\nxvals: \n";
  printMatrix(xvals);
  cout<<"\nyvals: \n";
  printMatrix(yvals);
  cout<<"\ngridvals: \n";
  printMatrix(gridvals);
}

vec2d Table::lookup(double IndepVar1, double IndepVar2)
{
  //Indep var 1 = xval
  //Indep var 2 = yval
  vec2d corner_indices = vec2d(4,2,-1);
  vector<double>:: iterator high;
  double xlow, xhigh, ylow, yhigh;

  // Make sure the value lies within the bounds of the table
  if ((IndepVar1 < xvals[0]) || (IndepVar1 > xvals[xvals.size()-1]) || (IndepVar2 < yvals[0]) || (IndepVar2 > yvals[yvals.size()-1]))
    {
      cout<<"Value ("<<IndepVar1<<", "<<IndepVar2<<") not within this table \n";
      cout<<"\tTable name: "<<table_name<<endl;
      exit(1);
      return corner_indices;
    }
  else
    {
      // Find the bracket indices for the given xval
      high = upper_bound(xvals.begin(),xvals.end(),IndepVar1);
      xhigh = double(high - xvals.begin());

      if (IndepVar1 == xvals[int(xhigh)]) 
	{
	  xlow = xhigh;
       	}
        else if (IndepVar1 == xvals[int(xhigh)-1])
        	{
        	  xhigh = xhigh-1;
        	  xlow = xhigh;
       	}
      else
	{
	  xlow = xhigh -1;
	}

      // Find the bracket indices for the given yval
      high = upper_bound(yvals.begin(),yvals.end(),IndepVar2);
      yhigh = double(high - yvals.begin());
      if (IndepVar2 == yvals[int(yhigh)]) 
	{
	  ylow = yhigh;
	}
        else if (IndepVar2 == yvals[int(yhigh)-1])
        	{
        	  yhigh = yhigh-1;
        	  ylow = yhigh;
        	}
      else
	{
	  ylow = yhigh-1;
	}
      
      // Return the results (location indices)
      corner_indices[0][0] = xlow;
      corner_indices[0][1] = ylow;
      
      corner_indices[1][0] = xlow;
      corner_indices[1][1] = yhigh;
      
      corner_indices[2][0] = xhigh;
      corner_indices[2][1] = ylow;
      
      corner_indices[3][0] = xhigh;
      corner_indices[3][1] = yhigh;
      
      return corner_indices;
    }
}

double Table::bilinear_interp(double IndepVar1, double IndepVar2) 
{
    double result;
   double fQ11, fQ12, fQ21, fQ22;
   double x, y, dx, dy, x1, x2, y1, y2, y3, y4;

  // double dblresult;
  // float result;
  // float fQ11, fQ12, fQ21, fQ22;
  // float x, y, dx, dy, x1, x2, y1, y2, y3, y4;


  int x1_index,x2_index,y1_index,y2_index;
  x = IndepVar1;
  y = IndepVar2;

  vec2d corner = lookup(x,y);

  x1_index = int(corner[0][0]);
  x2_index = int(corner[2][0]);
  y1_index = int(corner[0][1]);
  y2_index = int(corner[1][1]);

  x1 = xvals[ x1_index ];
  x2 = xvals[ x2_index];
  y1 = yvals[y1_index];
  y2 = yvals[y2_index];
  //  cout<<"Pressure brackets: "<<x1<<"\t"<<x2<<endl<<"Temperature brackets: "<<y1<<"\t"<<y2<<endl;
  //  printf("\nPressure brackets: %-12.8g \t %-12.8g\nTemperature brackets: %-12.8g \t %-12.8g \n",x1,x2,y1,y2);

  dx = x2-x1; 
  dy = y2-y1; 

  fQ11 = gridvals[y1_index][x1_index]; 
  fQ12 = gridvals[y2_index][x1_index]; 
  fQ21 = gridvals[y1_index][x2_index]; 
  fQ22 = gridvals[y2_index][x2_index]; 


  if ( (dx != 0) && (dy != 0) )
    {
      result =  (fQ11 * (x2-x) * (y2-y)) + (fQ21 * (x-x1) * (y2-y)) + (fQ12 * (x2-x) * (y-y1))+ (fQ22 * (x-x1) * (y-y1) ) ;
      result = result/(dx*dy); 
     }
  else if ( (dx == 0) && (dy != 0))
    {
      result = (1.0/dy) * ((fQ11 * (y2-y)) + (fQ22 * (y-y1)));
    }
  else if ( (dx !=0 ) && (dy == 0) )
    {
      result = (1.0/dx) * ((fQ11 * (x2-x)) + (fQ22 * (x-x1)));
    }
  else if ( (dx == 0 ) && (dy == 0) )
    {
      result = fQ11;
    }


  // // Debugging kludge:
  // cout<<"P vals: "<<x1<<"\t"<<x<<"\t"<<x2<<endl;
  // cout<<"T vals: "<<y1<<"\t"<<y<<"\t"<<y2<<endl;
  // cout<<"dP = "<<dx<<endl;
  // cout<<"dT = "<<dy<<endl;
  //  printf("\n fQ11 = %-12.8g \n fQ12 = %-12.8g \n fQ21 = %-12.8g \n fQ22 = %-12.8g",fQ11,fQ12,fQ21,fQ22);
   // cout<<"fQ11 = "<<fQ11<<endl;
   // cout<<"fQ12 = "<<fQ12<<endl;
   // cout<<"fQ21 = "<<fQ21<<endl;  
   // cout<<"fQ22 = "<<fQ22<<endl;
  //cout<<"results = "<<log10(result)<<endl;
  //   cout<<endl;

  //  result = pow(10.0,result);

  //  dblresult = result;
  //  return dblresult;
  return result;
}



OneD TableGroup::lookup(double P, double T)
{
  OneD result(4,0);
  double logP = log10(P);
  double logT = log10(T);
  
  //  result[0] = rho.bilinear_interp(P,T);
  // REMEMBER TO UNCOMMENT THE FOLLOWING LINES!!!
  result[0] = rho.bilinear_interp(logP,logT);
  result[1] = cp.bilinear_interp(logP,logT);
  result[2] = delta.bilinear_interp(logP,logT);
  result[3] = kappa.bilinear_interp(logP,logT);

  // Following line is a kludge
  //  result[0] = 0.9*result[0];
  //  result[1] = 0.9*result[1];
  //  result[2] = 0.9*result[2];
  //  result[3] = 0.9*result[3];

  return result;
}

//====================================================
// bundle method definitions 
//====================================================
void bundle::read_in_vars(string filename)
 {
   // Open the file and read in its contents
   ifstream myfile(filename.c_str());
   stringstream ss;
   string line, foo;
   OneD tempMwhole(jMax), tempMhalf(jMax), tempdMwhole(jMax), tempdMhalf(jMax), tempR(jMax), tempP(jMax), tempL(jMax), tempT(jMax), tempRho(jMax), temp(jMax,0), tempdx(jMax,0);
   int linenum = 0;

  if (myfile.is_open())
    { 
      while((! myfile.eof()) && (linenum < jMax))
	{
	  getline(myfile,line);
	  ss.clear();
	  ss.str(line);
	  ss >> ws;

	  if (line.find("//") != string::npos) // skip over comments in the input file
	    {
	      continue;
	    }


	  for (int word = 0; word < 8; word++)
	    { // 0, 1,  2, 3, 4, 5, 6, 7
	      // J, dM, M, P, R, L, T, RHO  
	      ss >> foo;
	      
	      if (word == 1)
		{
		  tempdMwhole[linenum] = atof(foo.c_str());
		}
	      if (word == 2)
		{
		  tempMwhole[linenum] = atof(foo.c_str());
		}
	      if (word == 3)
		{
		  tempP[linenum] = atof(foo.c_str());
		}
	      if (word == 4)
		{
		  tempR[linenum] = atof(foo.c_str());
		}
	      if (word == 5)
		{
		  tempL[linenum] = atof(foo.c_str());
		}
	      if (word == 6)
		{
		  tempT[linenum] = atof(foo.c_str());
		}

	      if (linenum == 0)
		{
		   tempMhalf[0] = 0.5 * tempMwhole[0]; //????
		   tempdMhalf[0] = tempMhalf[0];
		}
	      else
		{		  
		  tempMhalf[linenum] = (tempMwhole[linenum] + tempMwhole[linenum-1]) / 2.0; //?????
		  tempdMhalf[linenum] = tempMhalf[linenum] - tempMhalf[linenum-1];
		}
	    }

	  linenum++;
	}
    }
  else
    {
      cout<<"ERROR: cannot open the file "<<filename<<endl;
      exit(1);
    }


  // //  dMhalf = tempdMhalf;
  // for (int j =0; j < linenum; j++)
  //   {
  //     tempdMhalf[j] = (tempMhalf[j+1] - tempMhalf[j]);  //still need to contend with calculating dMhalf at the outer boundary, though... Make sure to come back to this.
  //   }
  // tempdMhalf[linenum] = tempMwhole[linenum] - tempMhalf[linenum];



  dMwhole = tempdMwhole;
  Mwhole = tempMwhole;
  dMhalf = tempdMhalf;
  Mhalf = tempMhalf;
  P = tempP;
  T = tempT;
  L = tempL;
  r = tempR;
  rho = temp;
  cP = temp;
  delta = temp;
  kappa = temp;
  Enuc = temp;
  grad = temp;
  oldP = P;
  oldT = T;
  dr = tempdx;
  dP = tempdx;
  dT = tempdx;
  dL = tempdx;
 } 

void bundle::eos_var_update(int i)
{
  OneD temp;
  int start, stop;
  if (i == -1)
    {
      start = 0;
      stop = jMax;
    }
  else
    {
      start = i;
      stop = i+1;
    }
    
  for (int j=start; j < stop; j++)
    {
      temp = EOS.lookup(P[j],T[j]);
      rho[j] = temp[0];
      cP[j] = temp[1];
      delta[j] = temp[2];
      kappa[j] = temp[3];
      
      double radgrad = 3.0 * kappa[j] * L[j] *P[j] / ( 16.0 * pi * gravG * a * c * Mhalf[j] * pow(T[j],4.0) );
      double adgrad = P[j] * delta[j] / (T[j] * rho[j] * cP[j]);
      grad[j] = min(adgrad,radgrad);
    }
}
//....................................................

void bundle::update_vars(bool is_the_update_xprime_based)
{
  // This method updates rho, delta, rad_grad, ad_grad, max_grad, cP, kappa, internal_energy and Enuc (well, not yet with Enuc), based on current values of x(r,P,T,L) and on the available lookup tables.
  double logP, logT, logAnswer, Answer, R, logR, T6;
  //  double ratio, temp, logkappa;
  double temp, logkappa;
  double maxlogkappa = 4.9; 
  double minlogkappa = -1.5;
  double ratio, dxratio;


  for (int j=0; j < jMax; j++)
    { 
      if (is_the_update_xprime_based)
	{

	  for (int i=0; i<iMax; i++)
	    {
	      if (i != 2)
		{
		  ratio = fabs( (x[i][j] - exp(xprime[i][j]) )/x[i][j] );
		  //		  dxratio = fabs( (dx[i][j] - exp(dxprime[i][j]) )/dx[i][j] );

		  if (ratio > 20.*DBL_EPSILON) 
		    {
		      x[i][j] = exp(xprime[i][j]); 
		    }
		  //		  if (dxratio > 20.*DBL_EPSILON)
		  //		    {
		      dx[i][j] = exp(dxprime[i][j]);
		      //		    }
		}	      
	      else
		{
		  x[i][j] = Ljup * xprime[i][j]; 
		  dx[i][j] = Ljup * dxprime[i][j];
		}
	    }

	  /*
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
	  */

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
      // logAnswer = EqnOfStateTable.bilinear_interp(logT,logP,EqnOfStateTable.i_rho); 
      Answer = pow(10.0,logAnswer); 
      rho[j] = Answer; 

      // Look up the internal energy (U) in the EOS table
      //logAnswer = EqnOfStateTable.bilinear_interp(logT,logP,EqnOfStateTable.i_internal_energy); 
      Answer = pow(10.0,logAnswer);
      internal_energy[j] = Answer; 
     

      // Look up the adiabatic gradient in the EOS table
      //logAnswer = EqnOfStateTable.bilinear_interp(logT,logP,EqnOfStateTable.i_ad_grad); 
      //      Answer = pow(10.0,logAnswer);
      // ad_grad[j] = logAnswer; 
  



      // Look up delta in the EOS table
      //logAnswer = EqnOfStateTable.bilinear_interp(logT,logP,EqnOfStateTable.i_delta); 
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
      //      logAnswer = HighTempKappaTable.bilinear_interp(logT,logR,HighTempKappaTable.i_kappa);
      Answer = pow(10.0,logAnswer);
      kappa[j] = Answer;
      

      /*

      // P. Bodenheimer things this kludge below may be giving me
      // a 'greenhouse effect' in my calcs.
      // TOTALLY KLUDGING THE KAPPA CALCULATION UNTIL I CAN
      // GET MY HANDS ON AN OPACITY TABLE THAT COVERS THESE
      // TEMP/DENSITY RANGES!!!
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
      */      


      // // FOR THE POLYTROPIC, IDEAL GAS EOS TEST CASE!
      // // Calculate rho, delta, ad_grad, and cP.
      // // Make sure to set ad_grad equal to grad, too.
  
      // // rho
      // Answer = x[0][j]/K;
      // rho[j] = pow(Answer,0.6);

      // // delta
      // Answer = 3.0*kB*rho[j]*x[3][j]/x[0][j];
      // delta[j] = Answer;

      // // ad_grad
      // ad_grad[j] =0.4;
      // grad[j] = ad_grad[j];

      // // cP
      // Answer = 3.0*kB/(2.0*mH);
      // cP[j] = Answer;

    } // End of loop over j



}
