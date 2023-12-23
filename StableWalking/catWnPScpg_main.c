//catWnPScpg_main.c
//Jessica Parker, November 20, 2021                                               
//
//This is the main function, which begins your program and guides the actions in your program. 

#include "catWnPScpg.h"  
#include "time.h" 
#include <math.h>

int main (void) { 

  int run1, run2, run3, run4, run5, rr1, rr2, rr3;   //Declaring some variables
  double tf0, tf1, tf2, tf3, tint; 

  run1 = 1;  //These numbers get written into the names of the data files. Set them to any integer you want
  run2 = 0;  //using whatever organization system you want.
  run3 = 0;
  run4 = 1;
  run5 = 0;

  cell2m = 1.0; //Set to 1 to apply pulse of conductance to both neurons. Set to 0 to apply pulse to only one neuron. 
  gModWE = 0.0; //Setting pulse conductances to zero, may be turned on later. These are global variables declared
  gModWI = 0.0; //in the header so make sure that you don't use these variable names in a different file for something else.
                //gModWE is used for an excitatory pulse, gModWI is used for an inhibitory pulse.
  double gMod0 = 1.0; //Maximal pulse conductance. When adding an excitatory pulse set gModWE = gMod0

  tf0 = 1000; //These are the integration times.
  tf1 = 2.862; 
  tf2 = 0.945; 
  tf3 = 30.0; 
  tint = 0.0001; //Integration time step. 
 
  clock_t start; //Declaring variables used to measure the run time.
  clock_t end; 
  float seconds; 

  int nvar = 16; //Number of variables in your set of differential equations.
  double yy[nvar]; //This will hold your simulation data.
  double yy0[nvar]; //This will hold your initial conditions.
  
  int a, b, c, d; //Declaring some variables used to index loops

  int numIP = 0;  //Used to read initial condition file
  double number = 0;
  FILE * f = fopen("ipW.txt", "r"); //Initial condition file.
  while( fscanf(f, "%lf,", &number) > 0 )  //Reading initial conditions
    {
      yy0[numIP]= number;
      numIP++;
    }
  fclose(f);

  for (a=0; a<nvar; a++)  //Setting time zero to initial conditions. You also have the option of doing
    {                     //this inside the for loop below. It depends on what you are trying to do.
      yy[a] = yy0[a];
    }

  for (b=0; b<1; b++)  //Use this for loop if you are sweeping a parameter, otherwise keep it as 
    {                    //(b=0; b<1; b++) 
      //tf1 = 2.568 + 0.0098*b; //Uncomment for parameter sweep. Set the beginning parameter value and step size here.
      //run3 = b+1;             //Use this to create a unique name for each simulation in a sweep. Written into ouput file name.
      for (c=0; c<1; c++)  //Use this for loop if you are running a 2D parameter sweep. Otherwise 
	{                    //keep it at (c=0; c<1; c++)
	  //tf2 = 0.8*c + 0.01; //Uncomment for 2D parameter sweep. Set the beginning value for you 2nd parameter and step size.
	  //run4 = c+1;         //Again creating a unique name for you output file if you are running a 2D sweep.

	  for (a=0; a<nvar; a++) //Comment this foor loop out if you are sweeping a parameter and you want
	    {                    //to take the last point of the previous simulation as your initial conditions,
	      yy[a] = yy0[a];    //but uncomment if you need each simulation to have the same initial conditions. 
	    } 
	  
	  printf("run2: %i\n", run2); 
	  printf("run3: %i\n", run3); 
	  printf("run4: %i\n", run4);
	  printf("run5: %i\n", run5);

	  start = clock();   //Measure run time for each simulation separately.
	  rr1=integrateNW(tf0, tint, nvar, yy); //This integrates your equations without writing the solution to an output file.
	  //                                        //It is used to integrate for a long time in order to reach stability without
	  //                                        //accumulating an immense amount of data. We usually use 1000 sec to reach stability.
	  gModWE = 0.0;
	  rr1=integrate(run1, run2, run3, run4, 0, tf3, tint, nvar, yy); //Only about 30 sec can be run at once, but that might depend on what computer you are
	                                                                 //using. So if you want to print out more time than out, split it up in pieces.

	  end = clock();  //Reading run time.
	  seconds = (float)(end-start)/CLOCKS_PER_SEC;	  
	  printf("running time: %6.6g\n", seconds); 
	}
    }
      
  return(0); 
} 
