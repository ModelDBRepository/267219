//catWnPScpg.h
//Jessica Parker, November 20, 2021
//
//This is the header file. Parameters are defined here.

#include <stdio.h>
#include <string.h>
#include <math.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

//Declare functions
int main (void);
int integrate( int run1, int run2, int run3, int run4, int run5, double tf, double tint, int nvar, double y[]);
int func(double t, const double y[], double f[], void * params);
int integrateNW(double tf, double tint, int nvar, double y[]);
double ** burstdata(double tint, int lengthy, int run1, int run2, int run3, int run4, int run5, int nrn, double y[]);

int numbs; //Used by burstdata.c

//Canonical Model Parameters
static const double gNaS = 3.83;
static const double gSynI = 5.5; 
static const double gL = 2.96;
static const double gCaS = 12.3;
static const double gK = 40.0;
static const double gNaF = 50.0;
static const double ENa  = 65.00; 
static const double ECa  = 160.0; 
static const double EK   = -70.0; 
static const double EL   = -54.0; 
static const double ESynI = -75.0; 
static const double V2mNaF = 20.00; 
static const double V2hNaF = 23.00; 
static const double V2mNaS = 42.00; 
static const double V2hNaS = 55.00; 
static const double V2mCaS = 45.59;        
static const double V2hCaS = 58.93;  
static const double V2mK   = 21.00; 
static const double V2Syn  = 0.000; 
static const double khCaS  = 0.750; 
static const double ThNaS = 0.100;
static const double ThCaS = 0.485; 
static const double TSynI = 0.009;

//Pulse Parameters
static const double EModE = 0.0; //Reversal potential for excitatory pulse of conductance.
static const double EModI = -75.0;  //Reversal potential for inhibitory pulse of conductance.
double gModWE;  //Conductance for excitatory pulse of conductance, used with EModE.
double gModWI;  //Conductance for inhibitory pulse of conductance, used with EModI.
double cell2m;  //Used to determine whether the pulse applies to both neurons or just neuron 1.
