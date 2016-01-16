//c++

#include <string>  
#include <sstream>
#include <fstream>
#include <cassert>    
#include <iostream>


// QUESO
#include <queso/GslVector.h>
#include <queso/GslMatrix.h>
#include <queso/BoxSubset.h>
#include <queso/InterpolationSurrogateBuilder.h>
#include <queso/InterpolationSurrogateIOASCII.h>
#include <queso/GaussianLikelihoodDiagonalCovariance.h>
#include <queso/InterpolationSurrogateIOASCII.h>
#include <queso/LinearLagrangeInterpolationSurrogate.h>
#include <queso/UniformVectorRV.h>
#include <queso/GenericVectorRV.h>
#include <queso/StatisticalInverseProblem.h>


template<class V, class M>
class Likelihood : public QUESO::GaussianLikelihoodDiagonalCovariance<V, M>
{
protected:
  QUESO::LinearLagrangeInterpolationSurrogate<V,M>* _flame_surrogate;


  // Instantiate GSL version of this class
  // template class QUESO::LinearLagrangeInterpolationSurrogate<QUESO::GslVector,QUESO::GslMatrix> flame_surrogate;
public:

  Likelihood(const char * prefix, const QUESO::VectorSet<V, M> & domain,
	     const V & observations, const V & covariance, QUESO::FullEnvironment& env , QUESO::InterpolationSurrogateIOASCII<QUESO::GslVector, QUESO::GslMatrix>&  data_reader )
    : QUESO::GaussianLikelihoodDiagonalCovariance<V, M>(prefix, domain,
							observations, covariance)
  {
  
    data_reader.read( "../surrogatebuilder/flamespeed.dat", env, "param_" );

    // Grab a reference to the data built in the reader
    const QUESO::InterpolationSurrogateData<V,M>& data = data_reader.data();

    // The reader read in the data, so now we can give the data
    // to the interpolation surrogate. This object can now be used in a likelihood
    // function for example. Here, we just illustrate calling the surrogate model
    // evaluation.
    _flame_surrogate = new QUESO::LinearLagrangeInterpolationSurrogate<V,M>( data );
  
  
  }

  virtual ~Likelihood()
  {
    delete _flame_surrogate;
  }

  virtual void evaluateModel(const V & domainVector, const V * domainDirection,
			     V & modelOutput, V * gradVector, M * hessianMatrix,
			     V * hessianEffect) const
  {
  
    double value = _flame_surrogate->evaluate(domainVector);
 
  
    // Evaluate model and fill up the m_modelOutput member variable
    for (unsigned int i = 0; i < modelOutput.sizeLocal(); i++) {
      modelOutput[i] = value;
      
      
      
      
      
    }
  }
};



int main(int argc, char ** argv) 

{
  /*
    if( argc < 4 )
    {
    // TODO: Need more consistent error handling.
    std::cerr << "Error: Must specify foward_run, model, and QUESO input files."
    << std::endl;
    exit(1); // TODO: something more sophisticated for parallel runs?
    }

    std::string model_inputfile = argv[1];
    std::string QUESO_input = argv[2];
  */
  //************************************************
  // Initialize environments
  //************************************************
  MPI_Init(&argc,&argv);

  


  QUESO::FullEnvironment env(MPI_COMM_WORLD, argv[1], "", NULL);
  QUESO::VectorSpace<QUESO::GslVector, QUESO::GslMatrix> paramSpace(env, "param_", 1, NULL);

  double min_val = 4.345;
  double max_val = 34.76;

  QUESO::GslVector paramMins(paramSpace.zeroVector());
  paramMins.cwSet(min_val);
  QUESO::GslVector paramMaxs(paramSpace.zeroVector());
  paramMaxs.cwSet(max_val);

  QUESO::BoxSubset<QUESO::GslVector, QUESO::GslMatrix> paramDomain("param_",paramSpace, paramMins, paramMaxs);

  QUESO::UniformVectorRV<QUESO::GslVector, QUESO::GslMatrix> priorRv("prior_",  paramDomain);

  // Set up observation space
  QUESO::VectorSpace<QUESO::GslVector, QUESO::GslMatrix> obsSpace(env,
								  "obs_", 1, NULL);

  // Fill up observation vector
  QUESO::GslVector observations(obsSpace.zeroVector());
  observations[0] = 2.1;
 
 
  QUESO::InterpolationSurrogateIOASCII<QUESO::GslVector, QUESO::GslMatrix>
    data_reader;
 
  QUESO::GslVector covariance(obsSpace.zeroVector());
  covariance[0] = 22.67573696;
 
  // Pass in observations to Gaussian likelihood object
    
  Likelihood<QUESO::GslVector, QUESO::GslMatrix> lhood("llhd_", paramDomain,
						       observations, covariance,env ,data_reader );
    
  QUESO::GenericVectorRV<QUESO::GslVector, QUESO::GslMatrix>
    postRv("post_", paramSpace);
   
      
      
    
  QUESO::GslVector paramInitials(paramSpace.zeroVector());

  paramInitials[0] = 17.38;

  QUESO::GslMatrix proposalCovMatrix(paramSpace.zeroVector());

  for (unsigned int i = 0; i < 1; i++) {
    proposalCovMatrix(i, i) = 11.1111;
  }
  
  QUESO::StatisticalInverseProblem<QUESO::GslVector,QUESO::GslMatrix> ip ("", NULL, priorRv, lhood, postRv);
  
  ip.solveWithBayesMetropolisHastings(NULL, paramInitials, &proposalCovMatrix);

  MPI_Finalize();
  
  return 0;
}

