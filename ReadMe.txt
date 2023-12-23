//Readme.txt
//Jessica Parker, November 31, 2021
//
//Instructions for Cat Locomotion and Paw-shaking CPG Model Code

***Software Required and Installation Steps

This code was built for a Linux or Mac computer. A virtual Linux machine on Windows can also be used. Below are instructions on the
software you will need. There are separate instructions for the Linux and for the Mac.

Linux:
- Open the terminal. You can find it with the launch pad.
- Install Homebrew if you don’t already have it, by entering the following line in the terminal.
  	  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
- Install the GSL scientific library with the following command:
  	  brew install gsl
- We use MATLAB for plotting the data, but you can use alternative software if you don't have access to MATLAB.

Mac:
- Open the terminal.
- Xcode needs to be installed.
- The Xcode command line tools also need to be installed.
      	  xcode-select –install
- Install Homebrew by entering the following line in the terminal.
  	  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
- Then, install the GSL scientific library with the following command:
  	  brew install gsl
- We use MATLAB for plotting the data, but you can use alternative software if you don't have access to MATLAB


***C Code for Integration and Analysis:

Enter directory /CatLocomotionPawShakingCPG/ in the terminal. There are three sets of C code for integrating the model and producing
simulations, one for an example of transient paw-shaking, one for the stable walking regime, and one for the stable paw-shaking regime.
Each set of code is in a separate directory. The three directories are: 

- /TransienceExample/ contains code that applies a pulse during the walking regime, which causes transient paw-shake-like activity
before returning to the walking regime. Data from this integration is saved in the subdirectory /data/.

- /StableWalking/ contains code that starts with walking initial conditions and runs for 1000 s to reach stability, but to save space no
output files are written for that 1000 s. Then, it runs another 30 s and saves the data to output files in the subdirectory /data/.

- /StablePawshaking/ contains code similar to /StableWalking/, but with paw-shaking initial conditions. Again, data is saved to subdirectory /data/.

Each of these directories contains the same code files except for one exception. Here is a description of the files in each directory.

Each directory contains:
     compl – compiles code
     catWnPScpg.h – header file, contains parameter values
     catWnPScpg_main.c – main file, directs the flow of the program
     catWnPScpg_integrate.c – integrates the model and save output data
     catWnPScpg_integrateNW.c – integrates without writing output files
     catWnPScpg_dy.c – defines differential equations used by integrate() and integrateNW()
     catWnPScpg_burstdata.c – analyzes burst data and measures burst characteristics
     ipW.txt – initial conditions from the stable walking regime
     ipPS4.txt – initial condition from the stable paw-shaking regime with 4 spikes per burst
     ipPS5.txt – initial conditions from the stable paw-shaking regime with 5 spikes per burst
     plotVt.m – MATLAB code that plots the voltage traces made by the C code.

First, the file compl is a bash script file that compiles the code for you so you don’t have to enter a long confusing line of code to the
terminal every time you want to run the code. It creates the executable file runCatCPG.exe. All you have to do is enter the following and the
code is compiled.
       ./compl

Next, let’s look at the header file, catWnPScpg.h. This is where all parameter values are stored. If you want to sweep a parameter, comment out
the initialization of the parameter variable and just declare it instead, and make sure that you don’t declare it again in any other file. 

The main file, catWnPScpg_main.c, is where the code begins and ends. It directs the flow of the program. If you want to change the numbers used
to make unique file names for your data (run1, run2, run3, run4, and run5), you change them here. If you want to run a parameter sweep or change
the pulse duration or pulse conductance, you do that here.

catWnPScpg_integrate.c is where the model is integrated and where the output data are written to files. This code saves the output to the directory
/data/ which is inside each of the three main directories. If you want to change where the data is saved to, then there are few different lines
of code where output file names are created. The voltage data and the other variables are saved in a file named V[run1]_[run2]_[run3]_[run4]_[run5].dat.
In the original example set up in the code, this would be V1_0_0_[run4]_[run5].dat, where run4 and run5 depend on which directory you are in. Burst
data is saved in files with the prefixes ‘bursts1J’ and ‘bursts2j’. There are also a couple files saved by catWnPScpg_burstdata.c, so make sure you
change those too.

catWnPScpg_integrateNW.c is another file that is used to integrate the model, except this one does not save any output data. It is used to quickly
integrate for an extended period of time to reach a stable state of the model.

catWnPScpg_dy.c is where all of the differential equations are defined. This is the substance of your model, so it is important to not change
anything here unless you have a backup copy.

catWnPScpg_burstdata.c analyzes the burst data and measures the following burst characteristics: time of burst onset, burst period (BP), spikes
per burst, spike frequency, duty cycle, burst duration (BD), and interburst interval (IBI). There is one additional output file created in this
function, which contains the indices of the spike times. They are written into output files with the prefixes ‘sps1j’ and ‘sps2j’.

plotVt.m is a MATLAB script that plots the voltage traces of your simulations. This file can be used to plot cases where a pulse is applied as well
as cases where it is a stable regime and no pulse is applied. Just set the variable pul = 1 if there is a pulse and 0 if there is not. This code
can be easily altered to plot other variables as well. 

There is also one additional file, plotTransEx.m, that is only in the directory /TransienceExample/. This is a MATLAB script that plots voltage
traces for a transient case, and it also plots BD, IBI, and curve fits of BD and IBI during transience. It also prints on top of the figure the
slopes of the curve fits of BD versus time and IBI versus time for both neuron 1 and neuron 2.


***Running the Code

To run the C code, You just need to compile and run. Enter the following lines in the terminal
	./compl. 
./runCatCPG.exe


***Plotting the Output

To plot the code, open MATLAB and open plotVt.m. Make sure the run numbers, specifically run1, run2, run3, and run4, coincide with the run numbers
in your data file names. Set xmin and xmax to the time range that you want to plot, where xmin is the beginning of the time range and xmax is the end
of the time range. If you are running the code in /TransienceExample/ where a pulse is applied, make sure the variable pul = 1, otherwise make sure
pul = 0. Then run the MATLAB script. It will create the figure and save it as pV[run1]_[run2]_[run3]_[run4]_[run5].eps. If you want to use a different
file type, go to where the file name is created at the bottom of the script where the function print() is called and change the file type designated
there. 

If you are in /TransienceExample/, open FigTransEx.m and again make sure the run numbers are set correctly and set xmin and xmax to the time range
that you want to plot. This will print the figure as pTransEx[run1]_[run2]_[run3]_[run4]_[run5].eps. 
