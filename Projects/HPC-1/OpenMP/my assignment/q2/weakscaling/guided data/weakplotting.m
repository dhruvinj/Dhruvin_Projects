clear all;close all;clc;
 p = dlmread('processors.dat');
 dyna(2-1) = dlmread('dataguided2.dat');
 dyna(3-1) =dlmread('dataguided3.dat');
 dyna(4-1) =dlmread('dataguided4.dat');
 dyna(5-1) =dlmread('dataguided5.dat');
 dyna(6-1) =dlmread('dataguided6.dat');
 dyna(7-1) =dlmread('dataguided7.dat');
 dyna(8-1) =dlmread('dataguided8.dat');
 dyna(9-1) =dlmread('dataguided9.dat');
 dyna(10-1) =dlmread('dataguided10.dat');
 dyna(11-1) =dlmread('dataguided11.dat');
 dyna(12-1) = dlmread('dataguided12.dat');
 dyna(13-1) =dlmread('dataguided13.dat');
 dyna(14-1) =dlmread('dataguided14.dat');
 dyna(15-1) =dlmread('dataguided15.dat');
 dyna(16-1) =dlmread('dataguided16.dat');
 dyna(17-1) =dlmread('dataguided17.dat');
 dyna(18-1) =dlmread('dataguided18.dat');
 dyna(19-1) =dlmread('dataguided19.dat');
 dyna(20-1) =dlmread('dataguided20.dat');
 dyna(21-1) =dlmread('dataguided21.dat');
 dyna(22-1) =dlmread('dataguided22.dat');
 dyna(23-1) =dlmread('dataguided23.dat');
 dyna(24-1) =dlmread('dataguided24.dat');
 dyna(25-1) =dlmread('dataguided25.dat');
 dyna(26-1) =dlmread('dataguided26.dat');
 dyna(27-1) =dlmread('dataguided27.dat');
 dyna(28-1) =dlmread('dataguided28.dat');
 dyna(29-1) = dlmread('dataguided29.dat');
 dyna(30-1) =dlmread('dataguided30.dat');
 dyna(31-1) =dlmread('dataguided31.dat');
 dyna(32-1) =dlmread('dataguided32.dat');
 
 for i=1:31
     s(i) = dyna(i);
 end
 plot(p,dyna,'r')