#!/bin/bash
echo -e "Solving for flamespeed"
mpiexec -np 16 ./1Run queso.in 2>&1 | tee run.log





























