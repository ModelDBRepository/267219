//catWnPScpg_burstdata.c
//Jessica Parker, November 20, 2021
//
//The burst characteristics and spike times are calculated in burstdata(), which is called to by integrate(). The indices
//of the spike times are written to file here. The burst characteristics are returned by burstdata(), and the burst
//characteristics are written to file by integrate().

#include "catWnPScpg.h"
#include <stdio.h>

double ** burstdata(double tint, int lengthy, int run1, int run2, int run3, int run4, int run5, int nrn, double y[])
{
  double spthresh = -10.0; //Spike voltage threshold
  double intbthresh = 0.04;  //Interburst interval (IBI) time threshold
  double bs[(int)lengthy/100][7]; //Declaring variable that will hold burst characteristics.
  int sps[(int)lengthy/10];  //Variable to carry spike indices. sps and bs are made extra large because we
                             //don't know how big they need to be yet.
  double maxy; 
  int maxa;
  int a = 0;
  int lntbs = 0;
  int lntsps = 0;
  int b = 0;
  int tbsps;
  int c;

  //Measures the time index of the peaks of all spikes.
  while (y[a] > spthresh)
    {
      a = a+1;
    }
  while (a < lengthy)
    {
      while ((y[a]<spthresh) && (a<lengthy))
	{
	  a = a+1;
	}
      maxy = -100;
      while ((y[a] > spthresh) && (a<lengthy))
	{
	  if (y[a] > maxy)
	    {
	      maxy = y[a];
	      maxa = a;
	    }
	  a = a+1;
	}
      sps[lntsps] = maxa;  //This holds the time index of the spike. So t[sps[3]] would be the time of the 3rd spike's peak.
      lntsps = lntsps + 1;
    }

  char f_2[100];
  sprintf(f_2,"./data/sps%iJ%i_%i_%i_%i_%i.txt",nrn,run1,run2,run3,run4,run5); //Saves spike indices to output file
  FILE * f2 = fopen(f_2,"w");
  for (int nn=0;nn<lntsps;nn++)
    {
      fprintf(f2,"%i \n", sps[nn]);
    }
  fclose(f2);

  int here;
  int next;
  double sper = 0; //Will hold interspike interval (ISI) values.
  double sfreq = 0; //Used to calculate spike frequency.
  tbsps = 0; 
  if (sps[0]*tint > intbthresh)  //If time of first spike is greater than IBI threshold ...
    {
      bs[lntbs][0] = sps[0]*tint;  //then the first burst starts with the first spike.
      while (sper <= intbthresh)  //Loop through following spikes until interspike interval (ISI)
        {                         //is greater than IBI threshold
          here = sps[b];
          next = sps[b+1];
          sper = (next*tint)-(here*tint); //Next ISI
          sfreq = sfreq + 1.0/sper; //Calculating spike frequency of first burst by adding all ISIs together.
          b = b + 1;
        }
      lntbs = lntbs + 1;  //Counts number of bursts
      bs[lntbs][0] = next*tint; //Time of max of first spike of burst                                                                                    
      if (lntbs > 0)
        {
          bs[lntbs-1][6] = sper; //interburst interval                                                                                                   
          bs[lntbs-1][5] = (here*tint) - bs[lntbs-1][0]; //burst duration                                                                                
          bs[lntbs-1][1] = (next*tint) - bs[lntbs-1][0]; //burst period                                                                                  
          bs[lntbs-1][2] = (double)(b - tbsps); //spikes per burst                                                                                     
          bs[lntbs-1][3] = sfreq/(bs[lntbs-1][2]-1); //spike frequency, calculated as average of Intraburst ISIs
          bs[lntbs-1][4] = bs[lntbs-1][5]/bs[lntbs-1][1]; //duty cycle                                                                                   
        }
      tbsps = b;
      lntbs = lntbs + 1;
    }  //So far we have measure burst characteristics just for the first burst if the first burst started with the first spike.

  sfreq = 0;
  while (b < lntsps-1)  //Now we use the same method as above for the rest of the bursts. Running loop through all remaining spikes.
    {
      here = sps[b];
      next = sps[b+1];
      sper = (next*tint)-(here*tint);
      if (sper > intbthresh) //If ISI is greater than IBI threshold, then next burst has started.
	{
	  bs[lntbs][0] = next*tint; //time of max of first spike of burst, starts after one whole interburst interval
	  if (lntbs > 0)
	    {
	      bs[lntbs-1][6] = sper; //interburst interval
	      bs[lntbs-1][5] = (here*tint) - bs[lntbs-1][0]; //burst duration
	      bs[lntbs-1][1] = (next*tint) - bs[lntbs-1][0]; //burst period
	      bs[lntbs-1][2] = b+1 - tbsps; //spikes per burst
	      bs[lntbs-1][3] = sfreq/(bs[lntbs-1][2]-1); //spike frequency
	      bs[lntbs-1][4] = bs[lntbs-1][5]/bs[lntbs-1][1]; //duty cycle
	    }
	  tbsps = b + 1;
	  lntbs = lntbs + 1;
	  sfreq = 0;
	}
      else 
	{
	  sfreq = sfreq + 1.0/sper; //Adding all ISIs together if they are not also IBIs.
	}
      b = b + 1;
    }

  numbs = lntbs-2; //Total number of bursts
  double ** BS; //Now we know the number of bursts, we can transfer burst data to a matrix of the correct size.
  if (numbs > 1)
    {
      BS = malloc(numbs*sizeof(double*));   
      if (BS==NULL)
	{
	  fprintf(stderr, "Error: Out of memory\n");
	  exit(-1);
	}
      
      int g;
      for (g=0; g<numbs; g++)
	{
	  BS[g] = malloc(7*sizeof(double)); 
	  if (BS[g]==NULL)
	    {
	      fprintf(stderr, "Error: Out of memory\n");
	      exit(-1);
	    }
	}
      
      int d;
      for (d=0; d<numbs; d++)
	{
	  BS[d][0] = bs[d][0];
	  BS[d][1] = bs[d][1];
	  BS[d][2] = bs[d][2];
	  BS[d][3] = bs[d][3];
	  BS[d][4] = bs[d][4];
	  BS[d][5] = bs[d][5];
	  BS[d][6] = bs[d][6];
	}
    }
  else
    {
      BS = malloc(2*sizeof(double*));   
      if (BS==NULL)
	{
	  fprintf(stderr, "Error: Out of memory\n");
	  exit(-1);
	}
      
      int g;
      for (g=0; g<2; g++)
	{
	  BS[g] = malloc(7*sizeof(double)); 
	  if (BS[g]==NULL)
	    {
	      fprintf(stderr, "Error: Out of memory\n");
	      exit(-1);
	    }
	}
      
      for (g=0; g<7; g++)
	{
	  BS[0][g] = 0.0;
	  BS[1][g] = 0.0;
	}
    }
  
  return BS; //return matrix of burst data.
}
      
      
      
