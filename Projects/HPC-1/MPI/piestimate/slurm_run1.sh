#!/bin/sh
#SBATCH --clusters=mae
#SBATCH --partition=planex
#SBATCH --account=pi-pbauman
#SBATCH --mem=64000
#SBATCH --time=01:00:00
#SBATCH --nodes=6
#SBATCH --ntasks-per-node=20
#SBATCH --job-name="lens_xx1"
#SBATCH --output=lens_xx1.out
#SBATCH --exclusive
#SBATCH --mail-user=tradowsk@buffalo.edu
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

export N_THREADS=1
export FINS_OPTIONS="--node_major_dofs -ksp_type gmres -pc_type bjacobi
-sub_pc_type ilu -ksp_max_it 100
-ksp_gmres_restart 30 -pc_factor_zeropivot 0 -sub_pc_factor_zeropivot 0 -snes_ls
basic -snes_convergence_test skip -snes_max_linear_solve_fail 100 -snes_max_fail
100 --disable-perflog --n_threads=$N_THREADS $FINS_USER_OPTIONS"

rm -rf $FINS_EX_DIR/lens_xx/output1/*
srun -n $NPROCS $FINS_DIR/bin/fins --input-file $FINS_EX_DIR/lens_xx/cylinder-5sp_air1.in $FINS_OPTIONS

#
echo "All Done!"
