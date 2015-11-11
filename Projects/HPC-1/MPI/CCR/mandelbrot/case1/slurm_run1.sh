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


srun -n 2 ./Run 200

srun -n 4 ./Run 400

srun -n 6 ./Run 600

srun -n 8 ./Run 800

srun -n 10 ./Run 1000

srun -n 12 ./Run 1200
 
srun -n 16 ./Run 1600

srun -n 20 ./Run 2000

srun -n 24 ./Run  2400

srun -n 30 ./Run 3000



#
echo "All Done!"
