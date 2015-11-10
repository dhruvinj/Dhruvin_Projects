#!/bin/sh
#SBATCH --clusters=mae
#SBATCH --partition=planex
#SBATCH --account=pi-pbauman
#SBATCH --mem=64000
#SBATCH --time=01:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --job-name="HPC-HW1"
#SBATCH --output=outputintel.out
#SBATCH --exclusive
#SBATCH --mail-user=dhruvinj@buffalo.edu
#SBATCH --mail-type=ALL
##SBATCH --requeue
#Specifies that the job will be requeued after a node failure.
#The default is that the job will not be requeued.

echo "SLURM_JOB_ID="$SLURM_JOB_ID
echo "SLURM_JOB_NODELIST"=$SLURM_JOB_NODELIST
echo "SLURM_NNODES"=$SLURM_NNODES
echo "SLURMTMPDIR="$SLURMTMPDIR

cd $SLURM_SUBMIT_DIR
echo "working directory = "$SLURM_SUBMIT_DIR

ulimit -s unlimited
#

echo "Launch LENS_XX with srun"
NPROCS=`srun --nodes=${SLURM_NNODES} bash -c 'hostname' |wc -l`
echo NPROCS=$NPROCS
export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so
export MV2_ENABLE_AFFINITY=0

srun ./runintel.sh 

#
echo "All Done!"
