//catWnPScpg_dy.c
//Jessica Parker, November 20, 2021
//
//The function func() contain definitions of the model differential equations. It is called to by integrate() and integrateNW().

#include "catWnPScpg.h"

int func(double t, const double y[], double f[], void * params)
{
  //dV1
  f[0]=-(gNaF*pow((1.0/(1.0+exp(-(y[0]+V2mNaF)/7.8))),3)*y[1]*(y[0]-ENa)   //Fast Sodium
	 +gNaS*y[2]*y[3]*(y[0]-ENa)					   //Slow Sodium
	 +gK*y[4]*y[4]*y[4]*y[4]*(y[0]-EK)			           //Potassium
	 +gCaS*y[5]*y[5]*y[5]*y[6]*(y[0]-ECa)			           //Slow Calcium
	 +gL*(y[0]-EL)							   //Leak
	 +gModWE*(y[0]-EModE)						   //Excitatory pulse
	 +gModWI*(y[0]-EModI)						   //Inhibitory pulse
	 +gSynI*y[14]*(y[0]-ESynI))/0.001;				   //Synaptic current

  //hNaF1
  f[1]=(1.0/(1.0+exp((y[0]+V2hNaF)/7.0))-y[1])/(0.03/(exp((y[0]+V2hNaF+17.0)/15.0)+exp(-(y[0]+V2hNaF+17.0)/16.0)));

  //mNaS1
  f[2]=(1.0/(1.0+exp(-(y[0]+V2mNaS)/4.1))-y[2])/0.001;

  //hNaS1
  f[3]=(1.0/(1.0+exp((y[0]+V2hNaS)/5.0))-y[3])/ThNaS;    

  //mK1 
  f[4]=(exp((y[0]+(V2mK+25.0))/40.0)+exp(-(y[0]+(V2mK+25.0))/50.0))/0.007*(1.0/(1.0+exp(-(y[0]+V2mK)/15.0))-y[4]);

  //mCaS1 
  f[5]=((1.0/(1.0+exp(-(y[0]+V2mCaS)/4.27)))-y[5])/
    (0.001/((0.02*(y[0]+(V2mCaS+2.41))/(1.0-exp((-(V2mCaS+2.41)-y[0])/4.5)))+(0.05*(-(V2mCaS+5.41)-y[0])/(1.0-exp((y[0]+(V2mCaS+5.41))/4.5)))));
  
  //hCaS1
  f[6]=(1.0/(1.0+exp((y[0]+V2hCaS)/khCaS))-y[6])/ThCaS;


  //dV2
  f[7] = -(gNaF*pow((1.0/(1.0+exp(-(y[7]+V2mNaF)/7.8))),3)*y[8]*(y[7]-ENa)
	   +gNaS*y[9]*y[10]*(y[7]-ENa)
	   +gK*y[11]*y[11]*y[11]*y[11]*(y[7]-EK)
	   +gCaS*y[12]*y[12]*y[12]*y[13]*(y[7]-ECa)
	   +gL*(y[7]-EL)
	   +gModWE*(y[7]-EModE)*cell2m
	   +gModWI*(y[7]-EModI)*cell2m
	   +gSynI*y[15]*(y[7]-ESynI))/0.001;
  
  //hNaF2
  f[8]=(1.0/(1.0+exp((y[7]+V2hNaF)/7.0))-y[8])/(0.03/(exp((y[7]+V2hNaF+17.0)/15.0)+exp(-(y[7]+V2hNaF+17.0)/16.0)));

  //mNaS2
  f[9]=(1.0/(1.0+exp(-(y[7]+V2mNaS)/4.1))-y[9])/0.001;

  //hNaS2
  f[10]=(1.0/(1.0+exp((y[7]+V2hNaS)/5.0))-y[10])/ThNaS;    

  //mK2
  f[11]=(exp((y[7]+(V2mK+25.0))/40.0)+exp(-(y[7]+(V2mK+25.0))/50.0))/0.007*(1.0/(1.0+exp(-(y[7]+V2mK)/15.0))-y[11]);

  //mCaS2
  f[12]=((1.0/(1.0+exp(-(y[7]+V2mCaS)/4.27)))-y[12])/
    (0.001/((0.02*(y[7]+(V2mCaS+2.41))/(1.0-exp((-(V2mCaS+2.41)-y[7])/4.5)))+(0.05*(-(V2mCaS+5.41)-y[7])/(1.0-exp((y[7]+(V2mCaS+5.41))/4.5)))));
  
  //hCaS2
  f[13]=(1.0/(1.0+exp((y[7]+V2hCaS)/khCaS))-y[13])/ThCaS;
  
  
  //Synaptic Activations
  //Synapse from neuron 2 onto neuron 1
  f[14]=(1.0/(1.0+exp(-(y[7]+V2Syn)/0.4))-y[14])/TSynI;
  
  //synapse from neuron 1 onto neuron 2
  f[15]=(1.0/(1.0+exp(-(y[0]+V2Syn)/0.4))-y[15])/TSynI;

  return GSL_SUCCESS;
}
