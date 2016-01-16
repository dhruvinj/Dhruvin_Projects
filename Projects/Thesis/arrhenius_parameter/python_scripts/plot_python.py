#!/usr/bin/python

import sys
import os
import glob

from mpl_toolkits.mplot3d import Axes3D
import matplotlib
from matplotlib import rc
rc('text',usetex=True)

# Different modes
# By default, you can "show()" the figure which gives you an interactive window
# and it will save a .png when you call savefig().
# PDF produces a .pdf file, but show() doesn't seem to work.
#matplotlib.use("PDF")

import matplotlib.pyplot as plot
import numpy as np
from scipy.stats import gaussian_kde
import h5py


h5_file = h5py.File('chain_data_1e7.h5', 'r')

print "Reading Data"
A3_data_1e7 = h5_file['constant_sample_1e7/A3']
E3_data_1e7= h5_file['constant_sample_1e7/E3']

A3_subdata_1e7 = A3_data_1e7[800000:10000000:400]
E3_subdata_1e7 = E3_data_1e7[800000:10000000:400]



h5_file = h5py.File('chain_data_2e7.h5', 'r')

print "Reading Data"
A3_data_2e7 = h5_file['constant_sample_2e7/A3']
E3_data_2e7= h5_file['constant_sample_2e7/E3']

A3_subdata_2e7 = A3_data_2e7[800000:20000000:400]
E3_subdata_2e7 = E3_data_2e7[800000:20000000:400]





h5_file = h5py.File('chain_data_5e7.h5', 'r')

print "Reading Data"
A3_data_5e7 = h5_file['constant_sample_5e7/A3']
E3_data_5e7= h5_file['constant_sample_5e7/E3']

A3_subdata_5e7 = A3_data_5e7[800000:50000000:400]
E3_subdata_5e7 = E3_data_5e7[800000:50000000:400]



h5_file = h5py.File('chain_data_9e7.h5', 'r')

print "Reading Data"
A3_data_9e7 = h5_file['constant_sample_9e7/A3']
E3_data_9e7= h5_file['constant_sample_9e7/E3']

A3_subdata_9e7 = A3_data_9e7[800000:90000000:400]
E3_subdata_9e7 = E3_data_9e7[800000:90000000:400]







tick_label_fontsize=18
axis_label_fontsize=18
matplotlib.rc('xtick', labelsize=tick_label_fontsize )
matplotlib.rc(('xtick.major','xtick.minor'),  pad=10)
matplotlib.rc('ytick', labelsize=tick_label_fontsize)

#fig = plt.figure()
#ax1 = fig.add_subplot(111)
#ax1.set_xlabel( r"$E_3$", fontsize=axis_label_fontsize)
#ax1.set_ylabel( "kde", fontsize=axis_label_fontsize)


x = linspace(10, 90, 5000)


print "Computing KDE"
density_1e7_e3 = gaussian_kde(E3_subdata_1e7)
density_2e7_e3 = gaussian_kde(E3_subdata_2e7)
density_5e7_e3 = gaussian_kde(E3_subdata_5e7)
density_9e7_e3 = gaussian_kde(E3_subdata_9e7)




print "Computing KDE"
density_1e7_a3 = gaussian_kde(A3_subdata_1e7)
density_2e7_a3 = gaussian_kde(A3_subdata_2e7)
density_5e7_a3 = gaussian_kde(A3_subdata_5e7)
density_9e7_a3 = gaussian_kde(A3_subdata_9e7)



print "Plotting KDE"


fig = plot.figure()
ax1 = fig.add_subplot(111)

gn = ax1.set_xlabel( r"$log(A_3)$", fontsize=axis_label_fontsize)
gcn = ax1.set_ylabel( "KDE", fontsize=axis_label_fontsize)

ax1.plot(x, density_1e7_a3(x),linestyle='-',color='k',lw=1,label='sample size 1e7')
ax1.plot(x, density_2e7_a3(x),linestyle='--',color='k',lw=1,label='sample size 2e7')
ax1.plot(x, density_5e7_a3(x),linestyle='-.',color='k',lw=1,label='sample size 5e7')
ax1.plot(x, density_9e7_a3(x),linestyle=':',color='k',lw=1,label='sample size 9e7')

handles, labels = ax1.get_legend_handles_labels()
ax1.legend(handles, labels)

ax1.grid(True)

fig.savefig("sample_conv_A3.pdf", bbox_inches='tight')


print "DONE WITH Figure"






#plt.plot(x, density_200_e3(x), '-k', linewidth=0.01 )
#plt.plot(x, density_150_e3(x), '--k', linewidth=0.01 ) 
#plt.plot(x, density_100_e3(x), '-.k', linewidth=0.01 ) 
#plt.plot(x, density_75_e3(x), ':k', linewidth=0.01 ) 
#plt.plot(x, density_50_e3(x),'*k', linewidth=0.01)

#plt.legend(['sample size 200', 'sample size 150', 'sample size 100', 'sample size 75', 'sample size 50'], loc='upper left')


#print "Saving Figure"
#plt.savefig("E3_constant_surrogate.pdf", bbox_inches='tight')

