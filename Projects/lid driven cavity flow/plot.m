% % Read output files into matlab
clear all;close all;clc;
u = dlmread('u.dat');
v = dlmread('v.dat');

x = dlmread('x.dat');
y = dlmread('y.dat');


% ############################################
% Visualization
% ############################################

%uq = u./sqrt(u.^2+v.^2);
%vq = v./sqrt(u.^2+v.^2);

figure;
subplot (2,1,1);
streamslice(x,y,u,v);
%hold on;
%quiver(x,y,uq,vq);
axis equal;
subplot (2,1,2);
quiver(x,y,u,v);
axis equal;