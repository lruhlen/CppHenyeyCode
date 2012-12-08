#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <vector>
#include "AboutThisRun.h"
#include "physicalConstants.h"
#include "global.h"
#include "ReadInArray.h"

using namespace std;


OneD atmos(double &Rout, double &Lout, double &dM, double &Mstar, TableGroup &eos)
{
  string tt = "\t";
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
  

  double M = Mstar;
  
  // Step 1
  double dTau = 0.001;
  
  // Step 2
  double Teff = pow( (Lout/(4.0*pi*sigmaBoltzman* pow(Rout,2) )),0.25);
  double TKO = Teff * pow( (0.75*dTau + 0.5) ,0.25);//1893.3 ;
  
  // Step 3
  double Pout, Pguess1, Pguess2, G1, G2, GD, kappa1, kappa2, littleG, ratio, delP, threshold ;
  OneD eosvals(4);

  //  Pguess1 = 87.966;
  
   Pout = pow(TKO,4.0) * 3.0 * a;
   Pout = max(pow(10.0,eos.kappa.xvals[0]),Pout);
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
   cout<<"\n----------------------\n";
   cout<<"First atmos values:\n";
   cout<<"P = "<<Pguess1<<endl;
   cout<<"T = "<<TKO<<endl;
   eosvals = eos.lookup(Pguess1,TKO);
   cout<<"rho = "<<eosvals[0]<<endl;
   cout<<"kappa = "<<eosvals[3]<<endl;
   cout<<"----------------------\n\n";

  //   Done defining atmospheric values at outermost point. Now do the
  //   rest of the atmosphere using Runge-Kutta integration...
  double factor, tau, rho, kappa, logT, logP, radnab, adnab, nab, cP, delta;
  double R = Rout, T = TKO, P = Pguess1, Mout = Mstar;
  double Mtemp, MTau23, Rtemp, RTau23, Mk1, Mk2, Mk3, Mk4, Pk1, Pk2, Pk3, Pk4, Rk1, Rk2, Rk3, Rk4, Tk1, Tk2, Tk3, Tk4;
  double dMk1=0, dMk2=0, dMk3=0, dMk4=0, dPk1=0, dPk2=0, dPk3=0, dPk4=0, dRk1=0, dRk2=0, dRk3=0, dRk4=0, dTk1=0, dTk2=0, dTk3=0, dTk4=0;
  double temp;
  
  double dMWhole= dM;
  double dMHalf = 0.9*dMWhole; 
  double MassLimitHalf =  dMHalf;
  double Mtwiddle, Rtwiddle;

  bool TauSwitch = true, MassLimitHalfSwitch = true;
  double Psurface, Tsurface, Rhosurface, Msurface, Rsurface; 

  //  OneD dTauVals(1358,0);
  //  dTauVals = ReadInArray("/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/Peter_atmos_dTau_values_v2.txt",1358);

  // OneD PeterPvals(1358,0), PeterTvals(1358,0), PeterMvals(1358,0), PeterRvals(1358,0), PeterTauvals(1358,0),PeterdTauvals(1358,0);
  // PeterPvals = ReadInArray("/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/atmos_vals/Peter_atmos_Ps2.txt",1358);
  // PeterTvals = ReadInArray("/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/atmos_vals/Peter_atmos_Ts2.txt",1358);
  // PeterMvals = ReadInArray("/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/atmos_vals/Peter_atmos_Ms2.txt",1358);
  // PeterRvals = ReadInArray("/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/atmos_vals/Peter_atmos_Rs2.txt",1358);
  // PeterTauvals = ReadInArray("/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/atmos_vals/Peter_atmos_taus2.txt",1358);
  // PeterdTauvals = ReadInArray("/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/atmos_vals/Peter_atmos_dtaus2.txt",1358);
  
  //  vec2d PeterMtempvals(1358,5,0);
  //  PeterMtempvals = ReadInArray("/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/atmos_vals/Peter_atmos_Mtemp_vals.txt",1358,5); 
  //  vec2d PeterKappas(1358,4);
  //  PeterKappas = ReadInArray("/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/atmos_vals/PeterKappas.txt",1358,4);

  //  vec2d PeterIntermedVals(1358,17);
  //  PeterIntermedVals = ReadInArray("/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/RK4_debugging_1.txt",1358,17);
  //  // J dMk[1-4] dRk[1-4] dPk[1-4] dTk[1-4]
  //  // 0  [1-4]    [5-8]    [9-12]   [13-16]

  //  vec2d PeterNablas(1358,4);
  //  PeterNablas = ReadInArray("/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/atmos_vals/PeterNablas.txt",1358,4);

  // Initialize some variables...
  dTau = 0.001;
  tau = 0.5*dTau;
  eosvals = eos.lookup(P,T);
  rho = eosvals[0];
  
  MTau23 = Mstar;
  Mtemp = Mstar;
  RTau23 = Rout;
  Rtemp = Rout;
  M = 0;
  R = 0;
  //  double Mout = M; 
  //  Rout = R;

  //  cout<<"// J\t Tau \t M \t R \t P \t T \n";
  // cout<<"J \t tau \t Mtwiddle \n";

  int j = 0;
  do
  // The following line is a temporary kludge to replace the two lines above.
  //int numsteps = 1358;
    //  vec3d outputvals(numsteps,9,4);
  //  for (int j =0; j < numsteps; j++)
     {	   

       tau += dTau;
       // tau = PeterTauvals[j];
       // dTau = PeterdTauvals[j];

// Hj = 0
// Htau = 1
// HM = 2
// HR = 3
// HP = 4
// HT = 5
//       cout<<j<<tt<<tau<<tt<<M<<tt<<R<<tt<<P<<tt<<T<<endl;
//       M = PeterMvals[j]; //doesn't help
//       R = PeterRvals[j]; //doesn't help
//       T = PeterTvals[j]; // HELPS!
       //       P = PeterPvals[j]; // HELPS!
       //       tau = PeterTauvals[j]; //doesn't help
       //dTau = PeterdTauvals[j];  //doesn't help


       factor = dTau;
       eosvals = eos.lookup(P,T);
       delta = eosvals[2];
       cP = eosvals[1];
       rho = eosvals[0];
       kappa = eosvals[3];
       //kappa = PeterKappas[j][0];

       if (TauSwitch) // if you haven't reached the tau=2/3 surface yet
	 {
	   Mtwiddle = 0;
	   Rtwiddle = 0;
	 } 
       else
	 {
	   Mtwiddle = M - MTau23;
	   Rtwiddle = R - RTau23;
	 }

       Mtemp = Mstar - Mtwiddle;
       Rtemp = Rout - Rtwiddle;
       
       // if (j%100 == 0)
       // 	 {
       // 	   cout<<j<<tt<<tau<<tt<<Mtemp<<endl;
       // 	 }
       

       radnab = (3 / (16*pi*gravG*a*c) ) * (kappa * Lout * P / (Mtemp*pow(T,4)) );
       adnab = delta * P / (cP * T * rho);
       nab = min(radnab,adnab);//*(T/P);
       //nab = PeterNablas[j][0];

       dMk1 = factor * 4.0*pi*pow(Rtemp,2)/kappa; //not this one
       //       dMk1 = PeterIntermedVals[j][1];
       dRk1 = factor * 1.0 / (rho * kappa); //not this one
       //dRk1 = PeterIntermedVals[j][5];
       dPk1 = factor * gravG * Mtemp / (kappa * pow(Rtemp,2)); // maybe this one
       //dPk1 = PeterIntermedVals[j][9];
       dTk1 = factor * gravG * Mtemp * T * nab / (pow(Rtemp,2)*kappa*P); // maybe this one
       //       dTk1 = PeterIntermedVals[j][13];
       
       // outputvals[j][0][0] = Mtemp;
       // outputvals[j][1][0] = Rtemp;
       // outputvals[j][2][0] = P;
       // outputvals[j][3][0] = T;
       // outputvals[j][4][0] = kappa;
       // outputvals[j][5][0] = rho;
       // outputvals[j][6][0] = nab*T/P;
       // outputvals[j][7][0] = radnab;
       // outputvals[j][8][0] = adnab;
     //------------------------------


       //------------------------------
       Mk2 = M + 0.5*dMk1;
       Rk2 = R + 0.5*dRk1;
       Pk2 = P + 0.5*dPk1;
       Tk2 = T + 0.5*dTk1;
       
       if (TauSwitch) // if you haven't reached the tau=2/3 surface yet
	 {
	   Mtwiddle = 0;
	   Rtwiddle = 0;
	 } 
       else
	 {
	   Mtwiddle = Mk2 - MTau23;
	   Rtwiddle = Rk2 - RTau23;
	 }

       Mtemp = Mstar - Mtwiddle;      
       Rtemp = Rout - Rtwiddle;

       eosvals = eos.lookup(Pk2,Tk2);
       delta = eosvals[2];
       cP = eosvals[1];
       rho = eosvals[0];
       kappa = eosvals[3];
       //       kappa = PeterKappas[j][1];
       radnab = (3 / (16*pi*gravG*a*c) ) * (kappa * Lout * Pk2 / (Mtemp*pow(Tk2,4)) );
       adnab = delta * Pk2 / (cP * Tk2 * rho);
       nab = min(radnab,adnab);//*(Tk2/Pk2);
       //       nab = PeterNablas[j][1];
       
       dMk2 = factor *4.0*pi*pow(Rtemp,2)/kappa; // not this one
       //dMk2 = PeterIntermedVals[j][2];
       dRk2 = factor *1.0 / (rho * kappa);	    //not this one
       //       dRk2 = PeterIntermedVals[j][6];
       dPk2 = factor * gravG * Mtemp / (kappa * pow(Rtemp,2)); // maybe this one
       //dPk2 = PeterIntermedVals[j][10];
       dTk2 = factor * gravG * Mtemp * Tk2 * nab / (pow(Rtemp,2)*kappa*Pk2); // maybe this one
       //       dTk2 = PeterIntermedVals[j][14];


       // outputvals[j][0][1] = Mtemp;
       // outputvals[j][1][1] = Rtemp;
       // outputvals[j][2][1] = Pk2;
       // outputvals[j][3][1] = Tk2;
       // outputvals[j][4][1] = kappa;
       // outputvals[j][5][1] = rho;
       // outputvals[j][6][1] = nab*Tk2/Pk2;
       // outputvals[j][7][1] = radnab;
       // outputvals[j][8][1] = adnab;

       //------------------------------
       
       //------------------------------	   
       Mk3 = M + 0.5*dMk2;
       Rk3 = R + 0.5*dRk2;
       Pk3 = P + 0.5*dPk2;
       Tk3 = T + 0.5*dTk2;

       if (TauSwitch) // if you haven't reached the tau=2/3 surface yet
	 {
	   Mtwiddle = 0;
	   Rtwiddle = 0;
	 } 
       else
	 {
	   Mtwiddle = Mk3 - MTau23;
	   Rtwiddle = Rk3 - RTau23;
	 }

       Mtemp = Mstar - Mtwiddle;
       Rtemp = Rout - Rtwiddle;

       eosvals = eos.lookup(Pk3,Tk3);
       delta = eosvals[2];
       cP = eosvals[1];
       rho = eosvals[0];
       kappa = eosvals[3];
       //       kappa = PeterKappas[j][2];
       radnab = (3 / (16*pi*gravG*a*c) ) * (kappa * Lout * Pk3 / (Mtemp*pow(Tk3,4)) );
       adnab = delta * Pk3 / (cP * Tk3 * rho);
       nab = min(radnab,adnab);//*(Tk3/Pk3);
       //nab = PeterNablas[j][2];

       dMk3 = factor * 4.0*pi*pow(Rtemp,2)/kappa; // not this one
       //       dMk3 = PeterIntermedVals[j][3]; 
       dRk3 = factor * 1.0 / (rho * kappa); // not this one
       //       dRk3 = PeterIntermedVals[j][7];
       dPk3 = factor * gravG * Mtemp / (kappa * pow(Rtemp,2)); // maybe this one
       //       dPk3 = PeterIntermedVals[j][11];
       dTk3 = factor * gravG * Mtemp * Tk3 * nab / (pow(Rtemp,2)*kappa*Pk3); // maybe this one
       //       dTk3 = PeterIntermedVals[j][15]; 

       // outputvals[j][0][2] = Mtemp;
       // outputvals[j][1][2] = Rtemp;
       // outputvals[j][2][2] = Pk3;
       // outputvals[j][3][2] = Tk3;
       // outputvals[j][4][2] = kappa;
       // outputvals[j][5][2] = rho;
       // outputvals[j][6][2] = nab*Tk3/Pk3;
       // outputvals[j][7][2] = radnab;
       // outputvals[j][8][2] = adnab;


       //------------------------------
       
       //------------------------------
       Mk4 = M + dMk3;
       Rk4 = R + dRk3;
       Pk4 = P + dPk3;
       Tk4 = T + dTk3;
 
       if (TauSwitch) // if you haven't reached the tau=2/3 surface yet
	 {
	   Mtwiddle = 0;
	   Rtwiddle = 0;
	 } 
       else
	 {
	   Mtwiddle = Mk4 - MTau23;
	   Rtwiddle = Rk4 - RTau23;
	 }

       Mtemp = Mstar - Mtwiddle;
       Rtemp = Rout - Rtwiddle;

       eosvals = eos.lookup(Pk4,Tk4);
       delta = eosvals[2];
       cP = eosvals[1];
       rho = eosvals[0];
       kappa = eosvals[3];        
       //       kappa = PeterKappas[j][3];
       radnab = (3.0 / (16.0*pi*gravG*a*c) ) * (kappa * Lout * Pk4 / (Mtemp*pow(Tk4,4.0)) );
       adnab = delta * Pk4 / (cP * Tk4 * rho);
       nab = min(radnab,adnab);//*(Tk4/Pk4); 
       //       nab = PeterNablas[j][3];
       
       dMk4 = factor * 4.0*pi*pow(Rtemp,2)/kappa; // not this one
       //       dMk4 = PeterIntermedVals[j][4];
       dRk4 = factor * 1.0 / (rho * kappa); // not this one
       //       dRk4 = PeterIntermedVals[j][8];
       dPk4 = factor * gravG * Mtemp / (kappa * pow(Rtemp,2));// maybe this one, though not quite as much?
       //dPk4 = PeterIntermedVals[j][12]; 
       dTk4 = factor * gravG * Mtemp * Tk4 * nab / (pow(Rtemp,2)*kappa*Pk4);      
       //       dTk4 = PeterIntermedVals[j][16]; // maybe this one, though not quite as much?

       // outputvals[j][0][3] = Mtemp;
       // outputvals[j][1][3] = Rtemp;
       // outputvals[j][2][3] = Pk4;
       // outputvals[j][3][3] = Tk4;
       // outputvals[j][4][3] = kappa;
       // outputvals[j][5][3] = rho;
       // outputvals[j][6][3] = nab*Tk4/Pk4;
       // outputvals[j][7][3] = radnab;
       // outputvals[j][8][3] = adnab;
 
       //------------------------------
        // if (j%100 == 0)
        // 	 {
        // 	   cout<<j<<tt;
        // 	   //	   cout<<"dM ratios:\t"<<dMk1/PeterIntermedVals[j][1]<<tt<<dMk2/PeterIntermedVals[j][2]<<tt<<dMk3/PeterIntermedVals[j][3]<<tt<<dMk4/PeterIntermedVals[j][4]<<endl;
        // 	   //	   cout<<"dR ratios:\t"<<dRk1/PeterIntermedVals[j][5]<<tt<<dRk2/PeterIntermedVals[j][6]<<tt<<dRk3/PeterIntermedVals[j][7]<<tt<<dRk4/PeterIntermedVals[j][8]<<endl;
        // 	   	   cout<<dPk1/PeterIntermedVals[j][9]<<tt<<dPk2/PeterIntermedVals[j][10]<<tt<<dPk3/PeterIntermedVals[j][11]<<tt<<dPk4/PeterIntermedVals[j][12]<<endl;
	// 	   //        	   cout<<dTk1/PeterIntermedVals[j][13]<<tt<<dTk2/PeterIntermedVals[j][14]<<tt<<dTk3/PeterIntermedVals[j][15]<<tt<<dTk4/PeterIntermedVals[j][16]<<endl;
        // 	   //	   cout<<j<<tt<<dTk1<<tt<<PeterIntermedVals[j][13]<<tt<<tt<<dTk4<<tt<<PeterIntermedVals[j][16]<<endl;
        // 	   //cout<<endl;
        // 	 }
       


       //------------------------------
       M += (1.0/6.0) * (dMk1 + 2.0*dMk2 + 2.0*dMk3 + dMk4);
       P += (1.0/6.0) * (dPk1 + 2.0*dPk2 + 2.0*dPk3 + dPk4);
       R += (1.0/6.0) * (dRk1 + 2.0*dRk2 + 2.0*dRk3 + dRk4);
       T += (1.0/6.0) * (dTk1 + 2.0*dTk2 + 2.0*dTk3 + dTk4);
       //------------------------------
       //------------------------------
       if ( (M >= MassLimitHalf) && MassLimitHalfSwitch )
  	 {
	   //	   cout<<"*** ";
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
	   //	   cout<<"*** ";
  	   MTau23 = M;
  	   RTau23 = R;
	   
	   //	   cout<<"Mtau2/3 = "<<MTau23<<endl;

  	   TauSwitch = false;
  	 }
       //------------------------------
       //------------------------------
        if(tau > 10)
	  {
	    //	   temp = min(1.08 * dTau , 1.0e2);
	    temp = min(1.08 * dTau , 1.0e-6);
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
	j++;
       //------------------------------
     }while (M <= dM);

  //  cout<<"RTau23 = "<<RTau23<<endl;
  //  cout<<"MTau23 = "<<MTau23<<endl;
  // // Print out those 'outputvals' debugging parameters
  //  cout<<"J\t Zat1\t Zat2\t Zat3\t Zat4\t Rat1\t Rat2\t Rat3\t Rat4\t P1\t P2\t P3\t P4\t T1\t T2\t T3\t T4\tAKK1\tAKK2\tAKK3\tAKK4\trho1\trho2\trho3\trho4\t tpnab1\t tpnab2\t tpnab3\t tpnab4\tradnab1 \t radnab2 \t radnab3 \t radnab4 \t adnab1 \t adnab2 \t adnab3 \t adnab4 \n";
  // cout<<"J\t Zat1\t Zat2\t Zat3\t Zat4\t Rat1\t Rat2\t Rat3\t Rat4\t P1\t P2\t P3\t P4\t T1\t T2\t T3\t T4\tAKK1\tAKK2\tAKK3\tAKK4\trho1\trho2\trho3\trho4 \t tpnab1\t tpnab2\t tpnab3\t tpnab4\n";
 // for (int j=0; j<numsteps; j++)
 //   {
 //     cout<<j;
 //     for (int var=0; var<9; var++)
 // 	{
 // 	  for(int k=0; k<4; k++)
 // 	    {	  
 // 	      cout<<tt<<outputvals[j][var][k];
 // 	    }
 // 	}
 //     cout<<endl;
 //   }
   // Msurface = M;
   // Rsurface = R;
   Msurface = Mtemp;
   Rsurface = Rtemp;


     returnvals[0] = Msurface;
     returnvals[1] = Rout-Rsurface;
     //     returnvals[1] = Rsurface;
     returnvals[2] = Psurface;
     returnvals[3] = Tsurface;
     returnvals[4] = Rhosurface;

     cout<<"Msurface: "<<Msurface<<"\nRout-Rsurface: "<<Rout-Rsurface<<"\nPsurface: "<<Psurface<<"\nTsurface: "<<Tsurface<<"\nRhoSurface: "<<Rhosurface<<endl;

  return returnvals;
}
