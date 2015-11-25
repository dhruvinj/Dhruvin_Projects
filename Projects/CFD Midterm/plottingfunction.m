clear all;close all;clc


x = dlmread('x.dat');

y = dlmread('y.dat');
u =dlmread('u.dat');
v = dlmread('v.dat')
p = dlmread('Output.dat')
contour(x,y,p)