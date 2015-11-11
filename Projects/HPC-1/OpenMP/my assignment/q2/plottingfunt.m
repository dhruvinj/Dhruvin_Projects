clear all;close all;clc;

p = dlmread('processors.dat');
GS = dlmread('speedupdataguided.dat');
DS = dlmread('speedupdatadynamic.dat');
SS = dlmread('speedupdatastatic.dat');

 SP = dlmread('nonparallel.dat');
 
for i=1:31
    speedstatic(i) = SP/SS(i);
    speeddynamic(i) = SP/DS(i);
    speedguided(i) = SP/GS(i);
end

% hold on
% plot(p,speedstatic, 'r')
% plot(p, speeddynamic, 'b')
% plot(p,speedguided, 'm')
% hold off

for i=1:31
    kpstatic(i) = (((1/speedstatic(i)) - (1/p(i))))/(1-(1/p(i)));
    kpdynamic(i) = (((1/speeddynamic(i)) - (1/p(i))))/(1-(1/p(i)));
    kpguided(i) = (((1/speedguided(i)) - (1/p(i))))/(1-(1/p(i)));
end
% 

hold on
plot(kpstatic, 'r')
plot(kpdynamic, 'b')
plot(kpguided, 'm')
hold off