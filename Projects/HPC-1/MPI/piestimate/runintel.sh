#!/bin/bash
echo -e "Problem  2 Solution: Output time in milliseconds"
echo -e "gcc compiler row major matrix addition"
./q2/Run1
echo -e "gcc compiler row major matrix addition with optimization -O3"
./q2/Run2
echo -e "gcc compiler column major matrix addition"
./q2/Run3
echo -e "gcc compiler column major matrix addition with optimization -O3"
./q2/Run4
echo -e "intel compiler row major matrix addition"
./q2/Run5
echo -e "intel compiler row major matrix addition with optimization -O2"
./q2/Run6
echo -e "intel compiler column major matrix addition"
./q2/Run7
echo -e "intel compiler column major matrix addition with optimization -O2"
./q2/Run8

echo -e "Problem  3 Solution: Output time in milliseconds and dot product of two vectors"
echo -e "gcc compiler dot product"
./q3/Run1
echo -e "gcc compiler dot product with optimization -O3"
./q3/Run2
echo -e "intel compiler dot product with ddot MKl library"
./q3/Run3
echo -e "gcc compiler dot product with ddot"
./q3/Run4



echo -e "Problem  4 Solution: Output time in milliseconds"
echo -e "gcc compiler matrix matrix"
./q4/Run1
echo -e "gcc compiler matrix multiplication with optimization -O3"
./q4/Run2
echo -e "intel compiler matrix multiplication with dgemm"
./q4/Run3









