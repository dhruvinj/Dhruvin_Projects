import h5py
import numpy

rawdata = numpy.loadtxt("ip_raw_chain_1e7.txt")

h5file = h5py.File("chain_data_1e7.h5", "w")

h5file.create_dataset("constant_sample_1e7/A3", data=rawdata[:,0])

h5file.create_dataset("constant_sample_1e7/E3", data=rawdata[:,1])


rawdat = numpy.loadtxt("ip_raw_chain_2e7.txt")

h5file = h5py.File("chain_data_2e7.h5", "w")

h5file.create_dataset("constant_sample_2e7/A3", data=rawdat[:,0])

h5file.create_dataset("constant_sample_2e7/E3", data=rawdat[:,1])



rawda = numpy.loadtxt("ip_raw_chain_5e7.txt")

h5file = h5py.File("chain_data_5e7.h5", "w")

h5file.create_dataset("constant_sample_5e7/A3", data=rawda[:,0])

h5file.create_dataset("constant_sample_5e7/E3", data=rawda[:,1])


rawd = numpy.loadtxt("ip_raw_chain_9e7.txt")

h5file = h5py.File("chain_data_9e7.h5", "w")

h5file.create_dataset("constant_sample_9e7/A3", data=rawd[:,0])

h5file.create_dataset("constant_sample_9e7/E3", data=rawd[:,1])
