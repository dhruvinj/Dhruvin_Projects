#!/bin/bash

echo -e "Solve for surrogate model"
	make clean
	
	make 
	
 mpiexec -np 10 ./2Run queso_input/queso_5e6.inp 2>&1 | tee 2run.log
 
 mv outputData outputData_5e6
 
 mpiexec -np 10 ./2Run queso_input/queso_7e6.inp 2>&1 | tee 2run.log
 
 mv outputData outputData_7e6
 
 mpiexec -np 10 ./2Run queso_input/queso_1e7.inp 2>&1 | tee 2run.log
 
  mv outputData outputData_1e7
  
  mpiexec -np 10 ./2Run queso_input/queso_5e7.inp 2>&1 | tee 2run.log
 
 mv outputData outputData_5e7

 mpiexec -np 10 ./2Run queso_input/queso_1e8.inp 2>&1 | tee 2run.log

 mv outputData outputData_1e8
 
 
 mkdir 25_kde
 
 mv outputData_5e6 25_kde/
 mv outputData_7e6 25_kde/
 mv outputData_1e7 25_kde/
 mv outputData_5e7 25_kde/
 mv outputData_1e8 25_kde/
 
 rm *.*~
 mv *.dat 25_kde/
