import h5py
import numpy

rawdata = numpy.loadtxt("ip_raw_chain.txt")

h5file = h5py.File("chain_data.h5", "w")

h5file.create_dataset("/zoidberg1/data/users/dhruvinj/three_parameter/mean_autocorr/E2", data=rawdata[:,0])

h5file.create_dataset("/zoidberg1/data/users/dhruvinj/three_parameter/mean_autocorr/E3", data=rawdata[:,1])

h5file.create_dataset("/zoidberg1/data/users/dhruvinj/three_parameter/mean_autocorr/A3", data=rawdata[:,2])


#h5file.create_dataset("/arrhenius_gamma_n_constant_gamma_cn/run0/Metropolis-Hastings/Ta_N_raw_chain", data=rawdata[:,2])
