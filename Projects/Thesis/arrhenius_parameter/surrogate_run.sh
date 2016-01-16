#!/bin/bash

echo -e "Solve for surrogate model"
	make clean
	
	make 
	
 mpiexec -np 10 ./2Run queso_input/queso_7e5.inp 2>&1 | tee 2run.log
 
 mv outputData outputData_7e5
 
 mpiexec -np 10 ./2Run queso_input/queso_1e6.inp 2>&1 | tee 2run.log
 
 mv outputData outputData_1e6
 
 mpiexec -np 10 ./2Run queso_input/queso_5e6.inp 2>&1 | tee 2run.log
 
  mv outputData outputData_5e6
  
  mpiexec -np 10 ./2Run queso_input/queso_1e7.inp 2>&1 | tee 2run.log
 
 mv outputData outputData_1e7

 mpiexec -np 8 ./2Run queso_input/queso_16e7.inp 2>&1 | tee 2run.log

 mv outputData outputData_16e7
 
 
 mkdir 150_kde
 
 mv outputData_7e5 150_kde/
 mv outputData_1e6 150_kde/
 mv outputData_5e6 150_kde/
 mv outputData_1e7 150_kde/
 mv outputData_16e7 150_kde/
 
 rm *.*~
 mv *.dat 150_kde/
