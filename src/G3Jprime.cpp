#include <iostream>
#include <vector>
#include <math.h>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "convert_to_vec2d.h"
#include "convert_from_vec2d.h"
#include "printMatrix.h"
#include "matrixMultiply.h"

using namespace std;


vector<double> G3Jprime(bundle vars)
{

  vector<double> result(jMax);

  for (int j=0; j < jMax; j++)
    {    

      if (j==0)
	{
	  result[j] = vars.xprime[2][j] - (vars.M[1][j]/Ljup) *(vars.Enuc[j] - (vars.cP[j]*(vars.x[3][j] - vars.x_old[3][j])/delta_t ) +  ( (vars.delta[j]/vars.rho[j]) * ( (vars.x[0][j]-vars.x_old[0][j])/delta_t )));

	}
      else
	{
	  result[j] = vars.xprime[2][j] - vars.xprime[2][j-1] - ((vars.M[1][j]-vars.M[1][j-1])/Ljup) *(vars.Enuc[j] - (vars.cP[j]*(vars.x[3][j] - vars.x_old[3][j])/delta_t ) +  ( (vars.delta[j]/vars.rho[j]) * ( (vars.x[0][j]-vars.x_old[0][j])/delta_t )));

	}


    }

  return result;
}


vector<double> G3Jprime(bundle vars, bundle varied_vars, int varied_param_index, int offset)
{

  vector<double> result(jMax);
  double temp_xprime, temp_x, temp_rho, temp_grad, temp_delta, temp_cP, temp_kappa, temp_internalenergy, temp_Enuc;
  

  
  for (int j=0; j <jMax ; j++)
    {
      
      // Deal with the offset variation business
      if ((j+offset >= 0) && (j+offset < jMax))
	{

	  temp_xprime = vars.xprime[varied_param_index][j+offset];
	  temp_x = vars.x[varied_param_index][j+offset];
	  temp_rho = vars.rho[j+offset];
	  temp_grad = vars.grad[j+offset];
	  temp_delta = vars.delta[j+offset];
	  temp_cP = vars.cP[j+offset];
	  temp_kappa = vars.kappa[j+offset];
	  temp_internalenergy = vars.internal_energy[j+offset];
	  temp_Enuc = vars.Enuc[j+offset];
	  
	  vars.xprime[varied_param_index][j+offset] = varied_vars.xprime[varied_param_index][j+offset];
	  vars.x[varied_param_index][j+offset] = varied_vars.x[varied_param_index][j+offset];
	  vars.rho[j+offset] = varied_vars.rho[j+offset];
	  vars.grad[j+offset] = varied_vars.grad[j+offset];
	  vars.delta[j+offset] = varied_vars.delta[j+offset];
	  vars.cP[j+offset] = varied_vars.cP[j+offset];
	  vars.kappa[j+offset] = varied_vars.kappa[j+offset];
	  vars.internal_energy[j+offset] = varied_vars.internal_energy[j+offset];
	  vars.Enuc[j+offset] = varied_vars.Enuc[j+offset];
	  

	}


      if (j==0) // Set the inner boundary condition
	{

	  result[j] = vars.xprime[2][j] - (vars.M[1][j]/Ljup) *(vars.Enuc[j] - (vars.cP[j]*(vars.x[3][j] - vars.x_old[3][j])/delta_t ) +  ( (vars.delta[j]/vars.rho[j]) * ( (vars.x[0][j]-vars.x_old[0][j])/delta_t )));

	}

      else
	{
	  result[j] = vars.xprime[2][j] - vars.xprime[2][j-1] - ((vars.M[1][j]-vars.M[1][j-1])/Ljup) *(vars.Enuc[j] - (vars.cP[j]*(vars.x[3][j] - vars.x_old[3][j])/delta_t ) +  ( (vars.delta[j]/vars.rho[j]) * ( (vars.x[0][j]-vars.x_old[0][j])/delta_t )));

	}

      // Finish dealing with the offset variation business
      if ((j+offset >= 0) && (j+offset < jMax))
	{
	  vars.xprime[varied_param_index][j+offset] = temp_xprime;
	  vars.x[varied_param_index][j+offset] = temp_x;
	  vars.rho[j+offset] = temp_rho;
	  vars.grad[j+offset] = temp_grad;
	  vars.delta[j+offset] = temp_delta;
	  vars.cP[j+offset] = temp_cP;
	  vars.kappa[j+offset] = temp_kappa;
	  vars.internal_energy[j+offset] = temp_internalenergy;
	  vars.Enuc[j+offset] = temp_Enuc;
	}
      

    }

  return result;


}
