#!/bin/sh
#SBATCH --clusters=mae
#SBATCH --partition=planex
#SBATCH --account=pi-pbauman
#SBATCH --mem=64000
#SBATCH --time=01:00:00
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=20
#SBATCH --job-name="pi_estimation"
#SBATCH --output=pi_estmation.out
#SBATCH --exclusive
#SBATCH --mail-user=dhruvinj@buffalo.edu
#SBATCH --mail-type=ALL
##SBATCH --requeue
#Specifies that the job will be requeued after a node failure.
#The default is that the job will not be requeued.


ulimit -s unlimited

module load gcc-ubceslab intel-mpi-ubceslab
export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so


srun -n 2 ./Run 

srun -n 4 ./Run 
srun -n 6 ./Run 

srun -n 8 ./Run 

srun -n 10 ./Run 

srun -n 12 ./Run 
 
srun -n 16 ./Run 

srun -n 20 ./Run 

srun -n 24 ./Run  

srun -n 30 ./Run 



#
echo "All Done!"
