clear all;close all;clc;

% p = dlmread('processors.dat');
% GS = dlmread('speedupdataguided.dat');
% DS = dlmread('speedupdatadynamic.dat');
% SS = dlmread('speedupdatastatic.dat');
% 
%  SP = dlmread('nonparallel.dat');
%  

% 
% for i=1:31
%     kpstatic(i) = (((1/speedstatic(i)) - (1/p(i))))/(1-(1/p(i)));
%     kpdynamic(i) = (((1/speeddynamic(i)) - (1/p(i))))/(1-(1/p(i)));
%     kpguided(i) = (((1/speedguided(i)) - (1/p(i))))/(1-(1/p(i)));
% end
% % 
% 
% hold on
% plot(kpstatic, 'r')
% plot(kpdynamic, 'b')
% plot(kpguided, 'm')
% hold off

% for i=1:16
%     processor(i) =i*2;
% end
 SP = dlmread('nonparallel.dat');
 SP = SP*1e-10;
 processor(1) =dlmread('piestimate2.dat');
 processor(2) =dlmread('piestimate4.dat');
 processor(3) =dlmread('piestimate8.dat');
 processor(4) =dlmread('piestimate10.dat');
 processor(5) =dlmread('piestimate16.dat');
 processor(6) =dlmread('piestimate20.dat');
 processor(7) =dlmread('piestimate32.dat');


time(1) =dlmread('timeval2.dat');
time(2) =dlmread('timeval4.dat');
time(3) =dlmread('timeval8.dat');
time(4) =dlmread('timeval10.dat');
time(5) =dlmread('timeval16.dat');
time(6) =dlmread('timeval20.dat');
time(7) =dlmread('timeval32.dat');

 for i=1:7
     speedup(i) = SP/time(i);
     
 end
 
 plot(processor,speedup, 'r')

 for i=1:7
     kp(i) = (((1/speedup(i)) - (1/processor(i))))/(1-(1/processor(i)));
 end
figure; plot(kp, 'b')
