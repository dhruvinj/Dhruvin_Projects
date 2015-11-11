clear all;close all;clc;

 for i=1:16
     processor(i) =i*2;
 end



time(1) =dlmread('timeval2.dat');

time(2) =dlmread('timeval4.dat');

time(3) =dlmread('timeval6.dat');

time(4) =dlmread('timeval8.dat');

time(5) =dlmread('timeval10.dat');

time(6) =dlmread('timeval12.dat');

time(7) =dlmread('timeval14.dat');

time(8) =dlmread('timeval16.dat');

time(9) =dlmread('timeval18.dat');

time(10) =dlmread('timeval20.dat');

time(11) =dlmread('timeval22.dat');

time(12) =dlmread('timeval24.dat');

time(13) =dlmread('timeval26.dat');

time(14) =dlmread('timeval28.dat');

time(15) =dlmread('timeval30.dat');

time(16) =dlmread('timeval32.dat');





 
 plot(processor,time, 'r')

 