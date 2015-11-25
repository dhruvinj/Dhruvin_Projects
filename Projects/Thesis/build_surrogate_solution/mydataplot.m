close all; clear all; clc; 

flamespeed = dlmread('flamespeed.dat');

parameter = dlmread('parameter.dat');


plot(parameter, flamespeed);
