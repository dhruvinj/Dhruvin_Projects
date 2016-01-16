#!/bin/bash
echo -e "Solving for flamespeed"
mpiexec -np 16 ./1Run 2>&1 | tee 1run.log 





























