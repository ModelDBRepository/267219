//catWnPScpg_integrate.c
//Jessica Parker, November 20, 2021
//
//The function integrate() integrates the model and writes output to data to files.

#include "catWnPScpg.h"

int integrate( int run1, int run2, int run3, int run4, int run5, double tf, double tint, int nvar, double y[])
{
  char file_name_string[100]; //Create output file name.
  sprintf(file_name_string,"./data/V%i_%i_%i_%i_%i.dat",run1,run2,run3,run4,run5); //Saves files into directory /[run1]_[run2]_[run3]/
                                                                                                      //For this example, saves to /1_0_0/.

  const gsl_odeiv_step_type * T = gsl_odeiv_step_rk8pd; //8th order Runge-Kutta adaptive step size
  gsl_odeiv_step * s = gsl_odeiv_step_alloc(T, nvar); //This variable tells the integrator what type of Runge-Kutta you are using.
  gsl_odeiv_control * c = gsl_odeiv_control_y_new(1e-8, 1e-9); //Absolute and relative tolerances
  gsl_odeiv_evolve * e = gsl_odeiv_evolve_alloc(nvar); //Variable needed by the integrator.

  double t, ti;  
  int ii,nn,status;

  double h = 1e-8; //Set initial stepsize
  double iLn=tf*(1.0/(0.1*tint)); //How many time points the integrator will calculate.
  double iLn2 = 0.1*iLn; //How many time points saved in the output file
  int ln2 = (int)iLn2;

  if (ln2 < iLn2)
    {
      ln2 = ln2+1;
    }
  
  gsl_matrix * Vs = gsl_matrix_alloc(ln2, nvar);   //Allocate space and declare data matrix variable
  gsl_odeiv_system sys = {func, NULL, nvar};   //This variable holds information about your set of differential equations which it reads from func(),
                                               //defined in CatLocomotionCPG_dy.c. This integrator does not use the Jacbion, so pass NULL in its place 

  double V1[ln2];  
  double V2[ln2];
  int tstep = 0; //Used to save every 10th time point.
  int J = 0;
  t=0; // reset time for convenience
  // integrator takes very small steps, but i only care about what happens once per 0.00001 seconds.
  for (ii=0; ii<=iLn; ii++)
    {
      ti = ii * tf/iLn;
      while (t < ti) //Integrator uses an adaptive step size to move accross a single fixed time step of 0.00001 seconds.
	{
	  status = gsl_odeiv_evolve_apply (e, c, s, &sys, &t, ti, &h, y); //Integration taking one adaptive step.
	  if (status !=GSL_SUCCESS)
	    {
	    break;
	    }
	  if (h<1e-14)
	    {
	    h=1e-14;
	    }
	}
      if (ii == tstep) //Output file only saves points every 0.0001 seconds apart, although integrator
	{              //integrates for every time point 0.00001 seconds apart. To restrict file size.
	  V1[J] = y[0];  //Variable used by burst analysis code
	  V2[J] = y[7];
	  for (nn=0; nn<nvar; nn++)
	    {
	      gsl_matrix_set(Vs,J,nn,y[nn]); //Saving output data into GSL matrix.
	    }
	  tstep = tstep + 10; 
	  J = J + 1;
	}
    }
  
  double ** bs1 = burstdata(tint, ln2, run1, run2, run3, run4, run5, 1, V1); //Burst analysis for neuron 1. 
  int lnbs1 = numbs;
  double ** bs2 = burstdata(tint, ln2, run1, run2, run3, run4, run5, 2, V2); //Burst analysis for neuron 2. These variables contain
  int lnbs2 = numbs;                                                              //burst time, burst period, spikes per burst, spike frequency,
                                                                                  //duty cycle, burst duration, and interburst interval
  FILE * f1 = fopen(file_name_string,"wb"); //Write data to file
  gsl_matrix_fwrite (f1,Vs);
  fclose(f1);

  //Free memory
  gsl_odeiv_evolve_free(e);
  gsl_odeiv_control_free(c);
  gsl_odeiv_step_free(s);
  gsl_matrix_free(Vs);

  if ((lnbs1 > 0) && (lnbs2 > 0))  //Writing burst analysis output files.
    {
      char f_2[100];
      sprintf(f_2,"./data/bursts1J%i_%i_%i_%i_%i.txt",run1,run2,run3,run4,run5);
      FILE * f2 = fopen(f_2,"w");
      for (nn=0;nn<lnbs1;nn++)
	{
	  fprintf(f2,"%9.9g %9.9g %9.9g %9.9g %9.9g %9.9g %9.9g\n", bs1[nn][0], bs1[nn][1], bs1[nn][2], bs1[nn][3], bs1[nn][4], bs1[nn][5], bs1[nn][6]);
	}
      fclose(f2);
      
      char f_3[100];
      sprintf(f_3,"./data/bursts2J%i_%i_%i_%i_%i.txt",run1,run2,run3,run4,run5);
      FILE * f3 = fopen(f_3,"w");
      for (nn=0;nn<lnbs2;nn++)
	{
	  fprintf(f3,"%9.9g %9.9g %9.9g %9.9g %9.9g %9.9g %9.9g\n", bs2[nn][0], bs2[nn][1], bs2[nn][2], bs2[nn][3], bs2[nn][4], bs2[nn][5], bs2[nn][6]);
	}
	fclose(f3);
    }
  
  char f_ipr[100];
  sprintf(f_ipr,"./data/ip%i_%i_%i_%i_%i.txt",run1,run2,run3,run4,run5); //Saving last point as initial conditions file for future use.
  FILE * f_ip2 = fopen(f_ipr,"w");
  for (nn=0;nn<16;nn++)
  {
    fprintf(f_ip2,"%14.14g\n", y[nn]);
  }
  fclose(f_ip2);

  //Freeing memory of burst analysis variables.
  for(nn=0;nn<lnbs1;nn++)
    {
      free(bs1[nn]);
    }
  free(bs1);
  for(nn=0;nn<lnbs2;nn++)
    {
      free(bs2[nn]);
    }
    free(bs2);
  return 0;
}
