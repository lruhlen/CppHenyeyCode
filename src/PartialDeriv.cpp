#include <iostream>
#include <vector>
#include <math.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "printVector.h"
#include "printMatrix.h"
#include "matrixTranspose.h"
#include "dotProduct.h"
#include "addMatrix.h"
#include "matrixMultiply.h"
#include "convert_to_vec2d.h"
#include "convert_from_vec2d.h"
#include "FindMax.h"

using namespace std;

/* This function can calculate regular partial derivs (shift =0), 
   as well as the C and E partial derivs (shift = -1 or 1, respectively)
 */

vector<double> PartialDeriv(vector<double> (*funct)(bundle &inputs), bundle vars, int OneToVary, int shift )

{
  if (debugflag>=4){cout<<"\t\t\t Starting PartialDeriv subroutine\n";}

  // Note: OneToVary should range between 0 and 3
  vector<double> first(jMax), second(jMax), denom(jMax), deltax(jMax);
  vector<double> result(jMax);
  int startindex = 0, endindex = jMax;
  double foo;

  if(debugflag>=3)
    { cout<<"\t\t\t In PartialDeriv.h, vars.x is:\n";
      printMatrix(vars.x);
    }

  deltax = matrixMultiply(0.00000001,vars.x[OneToVary]);

  if(debugflag>=3)
    { 
      cout<<"\t\t\t In PartialDeriv.h, deltax is:\n";
      printMatrix(deltax);
      cout<<"\n\t\t\tFor comparison, x is: \n";
      printMatrix(vars.x[OneToVary]);
    }


  bundle varied_vars;
  varied_vars = vars;
  
  varied_vars.x[OneToVary] = addMatrix(vars.x[OneToVary],deltax);
  

  varied_vars.update_vars(false);

  first = (*funct)(vars);
  second = (*funct)(varied_vars);
  

  //----------------------------
  // Ultimately,
  // result = (second - first)/dx
  //----------------------------

  //  first = matrixMultiply(-1.0,first);  
  //  result = addMatrix(first,second);

  if (shift == -1)
    {
      startindex = 1;
      endindex = jMax;
      result[0] = 0.0;
    }
  if (shift == 1)
    {
      startindex = 0;
      endindex = jMax-1;
      result[jMax-1] = 0;
    }


  
  for(int j=startindex; j< endindex; j++)
    {
      // sort of a kludgey fail-safe, for now
      if(deltax[j+shift]!=0)
	{
	  result[j] = (second[j] - first[j]) / deltax[j+shift];
	  cout<<deltax[j+shift]<<"\t";
	}
    }

  cout<<endl<<endl;

  if(debugflag>=4)
    { vector<double> TempFirst = matrixMultiply(-1.0,first);
      vector<double> numerator = addMatrix(second,TempFirst);
      double maxNumerator = FindMax(numerator);
      
      cout<<"\n\t\t\t Printing out the numerator values\n";
      printMatrix(numerator[0]);

      
      cout<<"\n\t\t\t Printing out the alleged numerator/denom values\n";
      printMatrix(result[0]);
      
    }
  return result;
}
