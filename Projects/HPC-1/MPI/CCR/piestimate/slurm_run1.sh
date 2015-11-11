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


srun -n 2 ./Run1 20000000

srun -n 4 ./Run1 40000000

srun -n 6 ./Run1 60000000

srun -n 8 ./Run1 80000000

srun -n 10 ./Run1 100000000

srun -n 12 ./Run1 120000000

srun -n 14 ./Run1 140000000

srun -n 16 ./Run1 160000000

srun -n 18 ./Run1 180000000

srun -n 20 ./Run1 200000000

srun -n 22 ./Run1 220000000

srun -n 24 ./Run1 240000000

srun -n 26 ./Run1 260000000

srun -n 28 ./Run1 28000000

srun -n 30 ./Run1 300000000

srun -n 32 ./Run1 320000000

#
echo "All Done!"
