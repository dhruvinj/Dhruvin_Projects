import h5py
import numpy

rawdata = numpy.loadtxt("testdata.dat")

h5file = h5py.File("chain_data.h5", "w")

h5file.create_dataset("/zoidberg1/data/users/dhruvinj/multiple_data/mean_autocorr/E2", data=rawdata[:,0])

h5file.create_dataset("/zoidberg1/data/users/dhruvinj/multiple_data/mean_autocorr/E3", data=rawdata[:,1])

#h5file.create_dataset("/arrhenius_gamma_n_constant_gamma_cn/run0/Metropolis-Hastings/Ta_N_raw_chain", data=rawdata[:,2])
