#!/usr/bin/python

import sys
import os
import glob

import matplotlib
from matplotlib import rc
rc('text',usetex=True)

# Different modes
# By default, you can "show()" the figure which gives you an interactive window
# and it will save a .png when you call savefig().
# PDF produces a .pdf file, but show() doesn't seem to work.
#matplotlib.use("PDF")

import matplotlib.pyplot as plot
from numpy import *
from scipy.stats import gaussian_kde,skew,skewtest,kurtosis
import h5py

h5_file = h5py.File('chain_data.h5', 'r')

print "Reading Data"
print "Reading Data"
E3_data = h5_file['/zoidberg1/data/users/dhruvinj/one_parameter/1000_kde/outputData_1e7']


E3_sub_data=E3_data[500000:10000000:50]

print "Computing stats"
E3_mean = mean(E3_sub_data)
E3_sigma = std(E3_sub_data)

#gamma_N_mean = mean(gamma_N_sub_data)
#gamma_N_sigma = std(gamma_N_sub_data)



print "E3 stats:"
print "Mean: ", E3_mean
print "Std. Dev.: ", E3_sigma
print "Skewness: ", skew(E3_sub_data)
print "Kurtosis: ", kurtosis(E3_sub_data)
print " "

def gaussian(mu,sigma,x):
    return 1.0/(sigma*sqrt(2*pi))*exp(-0.5*((x-mu)/sigma)**2);


tick_label_fontsize=18
axis_label_fontsize=18
matplotlib.rc('xtick', labelsize=tick_label_fontsize )
matplotlib.rc(('xtick.major','xtick.minor'),  pad=10)
matplotlib.rc('ytick', labelsize=tick_label_fontsize)

fig = plot.figure()
ax1 = fig.add_subplot(111)
ax1.set_xlabel( r"$E_3 [KJ/mol]$", fontsize=axis_label_fontsize)
ax1.set_ylabel( "Output Samples", fontsize=axis_label_fontsize)

print "Plotting Histogram"
ax1.hist( E3_sub_data, bins=250, align='mid' )

ax2 = ax1.twinx()

#print "Computing KDE"
#density = gaussian_kde(E3_data)

x = linspace(0, 70, 500)

print "Plotting KDE"
#ax2.plot( x, density(x), 'k--', linewidth=1 )
ax2.plot(x, gaussian(E3_mean,E3_sigma,x), 'r-', linewidth=1 )

ax2.set_xbound(lower=0, upper=70)
ax2.set_ylabel( "PDF", fontsize=axis_label_fontsize)
#ax1.ticklabel_format(style='sci', axis='x', scilimits=(0,0) )
#ax1.ticklabel_format(style='sci', axis='y', scilimits=(0,0) )

ax1.grid(True)

print "Saving Figure"
plot.savefig("E3.pdf", bbox_inches='tight')



plot.figure(2)
plot.xlabel( "E3", fontsize=axis_label_fontsize)
plot.ylabel( "Output Samples", fontsize=axis_label_fontsize)

p3 = plot.hist( E3_data[:], bins=250, align='mid' )
ax2 = plot.twinx()

density = gaussian_kde(E3_data[:])

x2 = linspace(0.4,0.6,500)

p4 = plot.plot( x2, density(x2), 'k-', linewidth=2 )




print "Showing figure"
plot.show()
