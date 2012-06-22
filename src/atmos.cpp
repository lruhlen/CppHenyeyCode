#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <vector>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
using namespace std;


OneD atmos(double &Rout, double &Lout, double &dM, double &Mstar, TableGroup &eos)
{
  OneD returnvals(5,0);
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  // Start of my sandboxing of the atmos code
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  
  // // A summary of the process I use in the first while-loop below to find the T, P, rho, and kappa starting values
  // // for the RK4 integration processes at the "outer/top/upper edge" of the star's atmosphere.
  //  /* Steps (paraphrased and modified from Greg's 1989 write-up)
  //     1. Start with dTau = 0.001
  //     2. Calculate the temperature as a function of optical depth (tau)
  //     3. Make an initial guess for the pressure (P)
  //     4. Use the T and P values from steps 2 & 3 to get rho (from the EOS lookup)
  //     5. Use rho and T to get a value for kappa (from opacity table lookup)
  //     6. Use the eqn. of hydrostatic equilibrium to get a revised value of P.
  //     7. Repeat steps 3 through 6 until the change in P values b/w iterations falls below some threshold
  //   */
  
  
  // double Lout = 4.737424999999999e34;
  // double Rout =  409456800000.000;
  double M = Mstar;
  
  // Step 1
  double dTau = 0.001;
  
  // Step 2
  double Teff = pow( (Lout/(4.0*pi*sigmaBoltzman* pow(Rout,2) )),0.25);
  double TKO = Teff * pow( (0.75*dTau + 0.5) ,0.25);
  
  // Step 3
  double Pout, Pguess1, Pguess2, G1, G2, GD, kappa1, kappa2, littleG, ratio, delP, threshold ;
  OneD eosvals(4);
  
  Pout = pow(TKO,4.0) * 3.0 * a;
  ratio = 1.0;
  threshold = pow(10.0,-5);
  littleG = gravG * M / (pow(Rout,2));
  GD = littleG *dTau;
  eosvals = eos.lookup(Pout,TKO);
  kappa1 = eosvals[3];
  Pguess1 = Pout + (GD/kappa1);
  
  //   Step 4
  while (ratio > threshold)
    {
      // Step 5
      eosvals = eos.lookup(Pguess1,TKO);
      kappa1 = eosvals[3];
      G1 = ((Pguess1 - Pout)*kappa1) - GD;
      
      Pguess2 = 1.001*Pguess1;
      eosvals = eos.lookup(Pguess2,TKO);
      kappa2 = eosvals[3];
      G2 = ((Pguess2-Pout)*kappa2) - GD;
      
      delP = -1.0* G1 *(Pguess1 - Pguess2) / (G1 - G2);
      
      Pguess1 += delP;
      ratio = 2*fabs(delP)/(Pguess1+Pguess2);
      
    }
  
  
  //   Done defining atmospheric values at outermost point. Now do the
  //   rest of the atmosphere using Runge-Kutta integration...
  double factor, tau, rho, kappa, logT, logP, radnab, adnab, nab, cP, delta;
  double R = Rout, T = TKO, P = Pguess1, Mout = Mstar;
  double Mtemp, MTau23, Rtemp, RTau23, Mk1, Mk2, Mk3, Mk4, Pk1, Pk2, Pk3, Pk4, Rk1, Rk2, Rk3, Rk4, Tk1, Tk2, Tk3, Tk4;
  double dMk1=0, dMk2=0, dMk3=0, dMk4=0, dPk1, dPk2, dPk3, dPk4, dRk1=0, dRk2=0, dRk3=0, dRk4=0, dTk1, dTk2, dTk3, dTk4;
  double temp;
  
  double dMWhole= dM;
  double dMHalf = 0.9*dMWhole;
  double MassLimitHalf = M - dMHalf;
  double MassLimitWhole = M - dMWhole;
  bool TauSwitch = true, MassLimitHalfSwitch = true;
  double Psurface, Tsurface, Rhosurface, Msurface, Rsurface; 

  // Initialize some variables...
  dTau = 0.001;
  tau = 0.5*dTau;
  eosvals = eos.lookup(P,T);
  rho = eosvals[0];
  MTau23 = 0;
  Mtemp = M;
  RTau23 = 0;
  Rtemp = R;
  //  double Mout = M; 
  //  Rout = R;
  
  //  cout<<"Initial M = "<<M<<"\t P = "<<P<<"\t R = "<<R<<"\t T = "<<T<<endl;
   // Testing out the new TableGroup data structure, with info on how to use its lookup method
   /*
     double P, T ;
     P = 2.4e3;
     T = 9.21e3;
     OneD foo = eos.lookup(P,T);
     string names="rho\tcp\tdelta\tkappa\n";
     cout<<names;
     printMatrix(foo);
   */

   int j = 1;
     do
     {	   	
       factor = dTau;
          
       //------------------------------       
       if (MTau23 != 0)
  	 {
  	   Mtemp = Mout - M + MTau23;
  	   Rtemp = Rout - R + RTau23;
  	 }
       else
  	 {
  	   Mtemp = Mout;
  	   Rtemp = Rout;
  	 }
       eosvals = eos.lookup(P,T);
       delta = eosvals[2];
       cP = eosvals[1];
       rho = eosvals[0];
       kappa = eosvals[3];

       radnab = (3 / (16*pi*gravG*a*c) ) * (kappa * Lout * P / (Mtemp*pow(T,4)) );
       adnab = delta * P / (cP * T * rho);
       nab = min(radnab,adnab);
       

       dMk1 = factor * -4.0*pi*pow(Rtemp,2)/kappa;
       dRk1 = factor * -1.0 / (rho * kappa);
       dPk1 = factor * gravG * Mtemp / (kappa * pow(Rtemp,2));
       dTk1 = factor * gravG * Mtemp * T * nab / (pow(Rtemp,2)*kappa*P);
       //------------------------------
       
       //------------------------------
       Mk2 = M + 0.5*dMk1;
       Rk2 = R + 0.5*dRk1;
       Pk2 = P + 0.5*dPk1;
       Tk2 = T + 0.5*dTk1;
       
       if (MTau23 != 0)
  	 {
  	   Mtemp = Mout - Mk2 + MTau23;
  	   Rtemp = Rout - Rk2 + RTau23;
  	 }
       else
  	 {
  	   Mtemp = Mout;
  	   Rtemp = Rout;
  	 }

       eosvals = eos.lookup(Pk2,Tk2);
       delta = eosvals[2];
       cP = eosvals[1];
       rho = eosvals[0];
       kappa = eosvals[3];
       radnab = (3 / (16*pi*gravG*a*c) ) * (kappa * Lout * Pk2 / (Mtemp*pow(Tk2,4)) );
       adnab = delta * Pk2 / (cP * Tk2 * rho);
       nab = min(radnab,adnab);
       
       dMk2 = factor * -4.0*pi*pow(Rtemp,2)/kappa;
       dRk2 = factor * -1.0 / (rho * kappa);	    
       dPk2 = factor * gravG * Mtemp / (kappa * pow(Rtemp,2));
       dTk2 = factor * gravG * Mtemp * Tk2 * nab / (pow(Rtemp,2)*kappa*Pk2);
       //------------------------------
       
       //------------------------------	   
       Mk3 = M + 0.5*dMk2;
       Rk3 = R + 0.5*dRk2;
       Pk3 = P + 0.5*dPk2;
       Tk3 = T + 0.5*dTk2;
          
       if (MTau23 != 0)
  	 {
  	   Mtemp = Mout - Mk3 + MTau23;
  	   Rtemp = Rout - Rk3 + RTau23;
  	 }
       else
  	 {
  	   Mtemp = Mout;
  	   Rtemp = Rout;
  	 }
             
       eosvals = eos.lookup(Pk3,Tk3);
       delta = eosvals[2];
       cP = eosvals[1];
       rho = eosvals[0];
       kappa = eosvals[3];
       radnab = (3 / (16*pi*gravG*a*c) ) * (kappa * Lout * Pk3 / (Mtemp*pow(Tk3,4)) );
       adnab = delta * Pk3 / (cP * Tk3 * rho);
       nab = min(radnab,adnab);

       dMk3 = factor * -4.0*pi*pow(Rtemp,2)/kappa;
       dRk3 = factor * -1.0 / (rho * kappa);
       dPk3 = factor * gravG * Mtemp / (kappa * pow(Rtemp,2));
       dTk3 = factor * gravG * Mtemp * Tk3 * nab / (pow(Rtemp,2)*kappa*Pk3);
       //------------------------------
       
       //------------------------------
       Mk4 = M + dMk3;
       Rk4 = R + dRk3;
       Pk4 = P + dPk3;
       Tk4 = T + dTk3;
 
       if (MTau23 != 0)
  	 {
  	   Mtemp = Mout - Mk4 + MTau23;
  	   Rtemp = Rout - Rk4 + RTau23;
  	 }
       else
  	 {
  	   Mtemp = Mout;
  	   Rtemp = Rout;
  	 }

       eosvals = eos.lookup(Pk4,Tk4);
       delta = eosvals[2];
       cP = eosvals[1];
       rho = eosvals[0];
       kappa = eosvals[3];        
       radnab = (3 / (16*pi*gravG*a*c) ) * (kappa * Lout * Pk4 / (M*pow(Tk4,4)) );
       adnab = delta * Pk4 / (cP * Tk4 * rho);
       nab = min(radnab,adnab);
       
       
       dMk4 = factor * -4.0*pi*pow(Rk4,2)/kappa;
       dRk4 = factor * -1.0 / (rho * kappa);
       dPk4 = factor * gravG * Mk4 / (kappa * pow(Rk4,2));
       dTk4 = factor * gravG * Mk4 * Tk4 * nab / (pow(Rk4,2)*kappa*Pk4);       
       //------------------------------
       
       
       //------------------------------
       M += (1.0/6.0) * (dMk1 + 2.0*dMk2 + 2.0*dMk3 + dMk4);
       P += (1.0/6.0) * (dPk1 + 2.0*dPk2 + 2.0*dPk3 + dPk4);
       R += (1.0/6.0) * (dRk1 + 2.0*dRk2 + 2.0*dRk3 + dRk4);
       T += (1.0/6.0) * (dTk1 + 2.0*dTk2 + 2.0*dTk3 + dTk4);
       //------------------------------


       
       //------------------------------
       if ( (M <= MassLimitHalf) && MassLimitHalfSwitch )
  	 {
	   //  	   cout<<"*** ";
  	   Psurface = P;
  	   Tsurface = T;
	   eosvals = eos.lookup(Psurface,Tsurface);
  	   Rhosurface = eosvals[0];
  	   MassLimitHalfSwitch = false;
  	 }
       //------------------------------


       //------------------------------
       if( (tau > (2.0/3.0)) && TauSwitch )
  	 {
	   //  	   cout<<"*** ";
  	   MTau23 = M;
  	   RTau23 = R;
	   
  	   TauSwitch = false;
  	 }
       //------------------------------

  
       //------------------------------
       if(tau > 10)
  	 {
  	   temp = min(1.08 * dTau , 9.2e4);
  	   dTau = max(temp , 1.01* dTau );
  	   dTau = 1.01* dTau;
  	 }
       else
  	 {
  	   if (tau > 0.1) 
  	     {
  	       dTau = 0.01;
  	     }
  	   if (tau > 0.8)
  	     {
  	      dTau = 0.05;
  	     }
  	 }
       //------------------------------
  
       //------------------------------
       tau = tau + dTau;
       //------------------------------
  
       //------------------------------
       // if (j%100 == 0)
       // 	 {
       // 	   cout<<"Step "<<j<<":\tdTau = "<<dTau<<"\t tau = "<<tau<<"\tM = "<<M<<"\tP = "<<P<<"\tR = "<<R<<"\t T = "<<T<<endl;
       // 	 }
       j++;
       //------------------------------


     } while (M >= MassLimitWhole);
        
     Msurface = M;
     Rsurface = R;

     returnvals[0] = Msurface;
     returnvals[1] = Rsurface;
     returnvals[2] = Psurface;
     returnvals[3] = Tsurface;
     returnvals[4] = Rhosurface;

  return returnvals;
}
