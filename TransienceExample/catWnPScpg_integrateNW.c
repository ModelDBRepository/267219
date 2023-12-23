//catWnPScpg_integrateNW.c
//Jessica Parker, November 20, 2021
//
//The model is integrated here, but data are not written to files. This function is used to integrate
//for a long time to reach stability without accumulating an immense amount of data.

#include "catWnPScpg.h"

int integrateNW(double tf, double tint, int nvar, double y[])
{
  const gsl_odeiv_step_type * T = gsl_odeiv_step_rk8pd; //8th order Runge-Kutta adaptive step size
  gsl_odeiv_step * s = gsl_odeiv_step_alloc(T, nvar); //This variable tells the integrator what type of Runge-Kutta you are using.
  gsl_odeiv_control * c = gsl_odeiv_control_y_new(1e-8, 1e-9); //Absolute and relative tolerances
  gsl_odeiv_evolve * e = gsl_odeiv_evolve_alloc(nvar); //Variable needed by the integrator.  

  double t = 0;
  int status;
  double h = 1e-8; //Set initial stepsize

  gsl_odeiv_system sys = {func, NULL, nvar};   //This variable holds information about your set of differential equations
                                               //which it reads from func, defined in CatLocomotionCPG_dy.c
                                               //This integrator does not use the Jacbion, so pass NULL in its place
  
  while (t < tf)  //Integrates with adaptive time step throughout entire time range. There are no fixed time steps for this part.
    {
      status = gsl_odeiv_evolve_apply (e, c, s, &sys, &t, tf, &h, y);  //Integration taking one adaptive step.
      if (status !=GSL_SUCCESS)
	{
	  break;
	}
      if (h<1e-14)
	{
	  h=1e-14;
	}
    }
 
  //Free memory
  gsl_odeiv_evolve_free (e);
  gsl_odeiv_control_free (c);
  gsl_odeiv_step_free (s);

  return 0;
}
