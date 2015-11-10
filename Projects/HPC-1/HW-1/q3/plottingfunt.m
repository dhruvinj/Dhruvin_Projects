clear all;close all;clc;

gwo = dlmread('gwo.dat');
go = dlmread('go.dat');
blas = dlmread('blas.dat');
mkl = dlmread('mkl.dat');
N = dlmread('nodes.dat');
% axis tight; 
figure;plot(N,gwo);title('gcc compiler'); xlabel('Size of Array (N)');ylabel('Time')
figure;plot(N,go);title('Optimized gcc compiler'); xlabel('Size of Array (N)');ylabel('Time')
figure;plot(N,blas);title('Blas library function ddot'); xlabel('Size of Array (N)');ylabel('Time')
figure;plot(N,mkl);title('Mkl library function ddot'); xlabel('Size of Array (N)');ylabel('Time')