clear all;close all;clc;
 p = dlmread('processors.dat');
 dyna(2-1) = dlmread('datafile2.dat');
 dyna(3-1) =dlmread('datafile3.dat');
 dyna(4-1) =dlmread('datafile4.dat');
 dyna(5-1) =dlmread('datafile5.dat');
 dyna(6-1) =dlmread('datafile6.dat');
 dyna(7-1) =dlmread('datafile7.dat');
 dyna(8-1) =dlmread('datafile8.dat');
 dyna(9-1) =dlmread('datafile9.dat');
 dyna(10-1) =dlmread('datafile10.dat');
 dyna(11-1) =dlmread('datafile11.dat');
 dyna(12-1) = dlmread('datafile12.dat');
 dyna(13-1) =dlmread('datafile13.dat');
 dyna(14-1) =dlmread('datafile14.dat');
 dyna(15-1) =dlmread('datafile15.dat');
 dyna(16-1) =dlmread('datafile16.dat');
 dyna(17-1) =dlmread('datafile17.dat');
 dyna(18-1) =dlmread('datafile18.dat');
 dyna(19-1) =dlmread('datafile19.dat');
 dyna(20-1) =dlmread('datafile20.dat');
 dyna(21-1) =dlmread('datafile21.dat');
 dyna(22-1) =dlmread('datafile22.dat');
 dyna(23-1) =dlmread('datafile23.dat');
 dyna(24-1) =dlmread('datafile24.dat');
 dyna(25-1) =dlmread('datafile25.dat');
 dyna(26-1) =dlmread('datafile26.dat');
 dyna(27-1) =dlmread('datafile27.dat');
 dyna(28-1) =dlmread('datafile28.dat');
 dyna(29-1) = dlmread('datafile29.dat');
 dyna(30-1) =dlmread('datafile30.dat');
 dyna(31-1) =dlmread('datafile31.dat');
 dyna(32-1) =dlmread('datafile32.dat');
 
 for i=1:31
     s(i) = dyna(i);
 end
 plot(p,dyna,'r')