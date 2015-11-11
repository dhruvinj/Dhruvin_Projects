clear all;close all;clc

 processor(1) =dlmread('mandelbrot2.dat');
 processor(2) =dlmread('mandelbrot4.dat');
  processor(3) =dlmread('mandelbrot6.dat');
 processor(4) =dlmread('mandelbrot8.dat');
 processor(5) =dlmread('mandelbrot10.dat');
 processor(6) =dlmread('mandelbrot12.dat');
 processor(7) =dlmread('mandelbrot16.dat');
 processor(8) =dlmread('mandelbrot20.dat');
 processor(9) =dlmread('mandelbrot24.dat');
 processor(10) =dlmread('mandelbrot30.dat');

time(1) =dlmread('timeval2.dat');
time(2) =dlmread('timeval4.dat');
time(3) =dlmread('timeval6.dat');
time(4) =dlmread('timeval8.dat');
time(5) =dlmread('timeval10.dat');
time(6) =dlmread('timeval12.dat');
time(7) =dlmread('timeval16.dat');
time(8) =dlmread('timeval20.dat');
time(9) =dlmread('timeval24.dat');
time(10) =dlmread('timeval30.dat');


 plot(processor,time, 'r')
