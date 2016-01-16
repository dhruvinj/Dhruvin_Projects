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


h5_file = h5py.File('chain_data_7e5.h5', 'r')

print "Reading Data"
E2_data_7e5 = h5_file['/zoidberg1/data/users/dhruvinj/multiple_data/constant_surrogate_7e5/E2']
E3_data_7e5= h5_file['/zoidberg1/data/users/dhruvinj/multiple_data/constant_surrogate_7e5/E3']




h5_file = h5py.File('chain_data_1e6.h5', 'r')

print "Reading Data"
E2_data_1e6 = h5_file['/zoidberg1/data/users/dhruvinj/multiple_data/constant_surrogate_1e6/E2']
E3_data_1e6= h5_file['/zoidberg1/data/users/dhruvinj/multiple_data/constant_surrogate_1e6/E3']





h5_file = h5py.File('chain_data_5e6.h5', 'r')

print "Reading Data"
E2_data_5e6 = h5_file['/zoidberg1/data/users/dhruvinj/multiple_data/constant_surrogate_5e6/E2']
E3_data_5e6= h5_file['/zoidberg1/data/users/dhruvinj/multiple_data/constant_surrogate_5e6/E3']





h5_file = h5py.File('chain_data_1e7.h5', 'r')

print "Reading Data"
E2_data_1e7 = h5_file['/zoidberg1/data/users/dhruvinj/multiple_data/constant_surrogate_1e7/E2']
E3_data_1e7= h5_file['/zoidberg1/data/users/dhruvinj/multiple_data/constant_surrogate_1e7/E3']





h5_file = h5py.File('chain_data_16e7.h5', 'r')

print "Reading Data"
E2_data_16e7 = h5_file['/zoidberg1/data/users/dhruvinj/multiple_data/constant_surrogate_16e7/E2']
E3_data_16e7 = h5_file['/zoidberg1/data/users/dhruvinj/multiple_data/constant_surrogate_16e7/E3']

tick_label_fontsize=18
axis_label_fontsize=18
matplotlib.rc('xtick', labelsize=tick_label_fontsize )
matplotlib.rc(('xtick.major','xtick.minor'),  pad=10)
matplotlib.rc('ytick', labelsize=tick_label_fontsize)



fig = plot.figure()
ax1 = fig.add_subplot(111)
ax1.set_xlabel( r"$E_2 and E_3$", fontsize=axis_label_fontsize)
ax1.set_ylabel( "kde", fontsize=axis_label_fontsize)


x = linspace(-40, 70, 5000)


print "Computing KDE"
density_7e5_e3 = gaussian_kde(E3_data_7e5)
density_1e6_e3 = gaussian_kde(E3_data_1e6)
density_5e6_e3 = gaussian_kde(E3_data_5e6)
density_1e7_e3 = gaussian_kde(E3_data_1e7)
density_16e7_e3 = gaussian_kde(E3_data_16e7)


print "Computing KDE"
density_7e5_E2 = gaussian_kde(E2_data_7e5)
density_1e6_E2 = gaussian_kde(E2_data_1e6)
density_5e6_E2 = gaussian_kde(E2_data_5e6)
density_1e7_E2 = gaussian_kde(E2_data_1e7)
density_16e7_E2 = gaussian_kde(E2_data_16e7)


print "Plotting KDE"
ax1.plot(x, density_7e5_e3(x), 'k-', linewidth=1 , label = 'sample size 7e5')
ax1.plot(x, density_1e6_e3(x), 'k--', linewidth=1 , label = 'sample size 1e6') 
ax1.plot(x, density_5e6_e3(x), 'k-.', linewidth=1 ,  label = 'sample size 5e6') 
ax1.plot(x, density_1e7_e3(x), 'k:', linewidth=1 ,  label = 'sample size 1e7') 
ax1.plot(x, density_16e7_e3(x),'k*', linewidth=1,  label = 'sample size 16e7')


print "Saving Figure"
plot.savefig("E3_E2_constant_surrogate.pdf", bbox_inches='tight')



