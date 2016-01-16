#!/bin/bash

echo -e "Solve for surrogate model"
	make clean
	
	make 
	
 ./2Run queso_input/queso_1e5.inp 2>&1 | tee 2run.log
 
 mv outputData outputData_1e5
 
 mpiexec -np 10 ./2Run queso_input/queso_1e6.inp 2>&1 | tee 2run.log
 
 mv outputData outputData_1e6
 
  ./2Run queso_input/queso_5e5.inp 2>&1 | tee 2run.log
 
  mv outputData outputData_5e5
  
  mpiexec -np 10 ./2Run queso_input/queso_5e6.inp 2>&1 | tee 2run.log
 
 mv outputData outputData_5e6

 mpiexec -np 10 ./2Run queso_input/queso_1e7.inp 2>&1 | tee 2run.log

 mv outputData outputData_1e7
 
 mkdir 1000_kde
 
 mv outputData_1e5 1000_kde/
 mv outputData_5e5 1000_kde/
 mv outputData_1e6 1000_kde/
 mv outputData_5e6 1000_kde/
 mv outputData_1e7 1000_kde/
 
 rm *.*~
 
 mv *.dat 1000_kde/
