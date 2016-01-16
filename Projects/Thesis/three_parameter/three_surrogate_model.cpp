//c++

#include <string>  
#include <sstream>
#include <fstream>
#include <cassert>    
#include <iostream>
#include <math.h>

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
#include "queso/GslOptimizer.h"
#include "queso/OptimizerMonitor.h"

template<class V, class M>
class Likelihood : public QUESO::GaussianLikelihoodDiagonalCovariance<V, M>
{
protected:
  
 // QUESO::LinearLagrangeInterpolationSurrogate<V,M>* _flame_surrogate_20;
 // QUESO::LinearLagrangeInterpolationSurrogate<V,M>* _flame_surrogate_28;
  QUESO::LinearLagrangeInterpolationSurrogate<V,M>* _flame_surrogate_40;
	QUESO::LinearLagrangeInterpolationSurrogate<V,M>* _flame_surrogate_46;
  QUESO::LinearLagrangeInterpolationSurrogate<V,M>* _flame_surrogate_53;
  QUESO::LinearLagrangeInterpolationSurrogate<V,M>* _flame_surrogate_75;
	QUESO::LinearLagrangeInterpolationSurrogate<V,M>* _flame_surrogate_100;
	 
	 
	 
	// QUESO::InterpolationSurrogateIOASCII<V,M>* _interp_20;
	// QUESO::InterpolationSurrogateIOASCII<V,M>* _interp_28;
	 QUESO::InterpolationSurrogateIOASCII<V,M>* _interp_40;
	 QUESO::InterpolationSurrogateIOASCII<V,M>* _interp_46;
	 QUESO::InterpolationSurrogateIOASCII<V,M>* _interp_53;
	 QUESO::InterpolationSurrogateIOASCII<V,M>* _interp_75;
	 QUESO::InterpolationSurrogateIOASCII<V,M>* _interp_100;
 // Instantiate GSL version of this class
 // template class QUESO::LinearLagrangeInterpolationSurrogate<QUESO::GslVector,QUESO::GslMatrix> flame_surrogate;
public:

  Likelihood(const char * prefix, const QUESO::VectorSet<V, M> & domain,
      const V & observations, const V & covariance, QUESO::FullEnvironment& env , QUESO::InterpolationSurrogateIOASCII<QUESO::GslVector, QUESO::GslMatrix>&  data_reader )
    : QUESO::GaussianLikelihoodDiagonalCovariance<V, M>(prefix, domain,
        observations, covariance)
  {
  
   
  
   //std::string flame_20_filename = "flamespeed_20.dat";     
   //std::string flame_28_filename = "flamespeed_28.dat";
   std::string flame_40_filename = "flamespeed_40.dat";
   std::string flame_46_filename = "flamespeed_46.dat";
   std::string flame_53_filename = "flamespeed_53.dat";
   std::string flame_75_filename = "flamespeed_75.dat";
   std::string flame_100_filename = "flamespeed_100.dat";
  
  
  
  
  
  //_interp_20 = new QUESO::InterpolationSurrogateIOASCII<V,M>;
  //_interp_28 = new QUESO::InterpolationSurrogateIOASCII<V,M>;
  _interp_40 = new QUESO::InterpolationSurrogateIOASCII<V,M>;
  _interp_46 = new QUESO::InterpolationSurrogateIOASCII<V,M>;
  _interp_53 = new QUESO::InterpolationSurrogateIOASCII<V,M>;
  _interp_75 = new QUESO::InterpolationSurrogateIOASCII<V,M>;
  _interp_100 =new QUESO::InterpolationSurrogateIOASCII<V,M>;
  
  
 
  //_interp_20->read( flame_20_filename, env, "param_");
  //_interp_28->read( flame_28_filename, env, "param_");
  _interp_40->read( flame_40_filename, env, "param_");
  _interp_46->read( flame_46_filename, env, "param_");  
  _interp_53->read( flame_53_filename, env, "param_");
  _interp_75->read( flame_75_filename, env, "param_");
  _interp_100->read( flame_100_filename, env, "param_");
  
   /*
   data_reader.read( "flamespeed.dat", env, "param_" );
   data_reader.read( "flamespeed_100.dat", env, "param_" );
*/
  // Grab a reference to the data built in the reader
//  const QUESO::InterpolationSurrogateData<V,M>& data = data_reader.data();

  // The reader read in the data, so now we can give the data
  // to the interpolation surrogate. This object can now be used in a likelihood
  // function for example. Here, we just illustrate calling the surrogate model
  // evaluation.
  

  //_flame_surrogate_20 = new QUESO::LinearLagrangeInterpolationSurrogate<V,M> ( _interp_20->data() ); 
  //_flame_surrogate_28 = new QUESO::LinearLagrangeInterpolationSurrogate<V,M> ( _interp_28->data() );
  _flame_surrogate_40 = new QUESO::LinearLagrangeInterpolationSurrogate<V,M> ( _interp_40->data() );
  _flame_surrogate_46 = new QUESO::LinearLagrangeInterpolationSurrogate<V,M> ( _interp_46->data() );
  _flame_surrogate_53 = new QUESO::LinearLagrangeInterpolationSurrogate<V,M> ( _interp_53->data() );
  _flame_surrogate_75 = new QUESO::LinearLagrangeInterpolationSurrogate<V,M> ( _interp_75->data() );
  _flame_surrogate_100 = new QUESO::LinearLagrangeInterpolationSurrogate<V,M> ( _interp_100->data() );
  
  }

  virtual ~Likelihood()
  {
  
  
     
    // delete  _flame_surrogate_20;
    // delete  _flame_surrogate_28;
     delete  _flame_surrogate_40;
     delete  _flame_surrogate_46;
     delete  _flame_surrogate_53;
     delete  _flame_surrogate_75;
     delete  _flame_surrogate_100;
     
     

    //  delete _interp_20;
    //  delete _interp_28;
      delete _interp_40;
      delete _interp_46;
      delete _interp_53;
      delete _interp_75;
      delete _interp_100;
  }

  virtual void evaluateModel(const V & domainVector, const V * domainDirection,
      V & modelOutput, V * gradVector, M * hessianMatrix,
      V * hessianEffect) const
  {
   

   //double value_20 = _flame_surrogate_20->evaluate(domainVector);
   //double value_28 = _flame_surrogate_28->evaluate(domainVector);
   double value_40 = _flame_surrogate_40->evaluate(domainVector);
   double value_46 = _flame_surrogate_46->evaluate(domainVector);
   double value_53 = _flame_surrogate_53->evaluate(domainVector);
   double value_75 = _flame_surrogate_75->evaluate(domainVector);
   double value_100 = _flame_surrogate_100->evaluate(domainVector);
  
 
  
    // Evaluate model and fill up the m_modelOutput member variable
    for (unsigned int i = 0; i < modelOutput.sizeLocal(); i++) {
      
      
     // modelOutput[0] = value_20;
     // modelOutput[1] = value_28;
      modelOutput[0] = value_40;
      modelOutput[1] = value_46;    
      modelOutput[2] = value_53;
      modelOutput[3] = value_75;
      modelOutput[4] = value_100;
      
    }
  }
};


int main(int argc, char ** argv) 

{
  
  MPI_Init(&argc,&argv);

  

  QUESO::FullEnvironment env(MPI_COMM_WORLD, argv[1], "", NULL);
  QUESO::VectorSpace<QUESO::GslVector, QUESO::GslMatrix> paramSpace(env, "param_", 3, NULL);
  QUESO :: GslVector paramMinValues ( paramSpace . zeroVector ());
  QUESO :: GslVector paramMaxValues ( paramSpace . zeroVector ());

  // the pre-exponential factor variation of O + O3 [=] O2 + O2 reaction(3)
  // paramMinValues [0] = log(1.3e+12);
  // paramMaxValues [0] = log(10.4e+12);
  paramMinValues [0] = -20;
    paramMaxValues [0] = 40;

    // the activation energy variation of O + O3 [=] O2 + O2 reaction(3)
    paramMinValues [1] = -30;
    paramMaxValues [1] = 90;



     paramMinValues [2] = log(7.201e+10);
    paramMaxValues [2] = log(2.5e+17);

  QUESO::BoxSubset<QUESO::GslVector, QUESO::GslMatrix> paramDomain("param_",paramSpace, paramMinValues, paramMaxValues);


  QUESO::UniformVectorRV<QUESO::GslVector, QUESO::GslMatrix> priorRv("prior_",  paramDomain);

  // Set up observation space
  QUESO::VectorSpace<QUESO::GslVector, QUESO::GslMatrix> obsSpace(env,
								  "obs_", 5, NULL);

  // Fill up observation vector
  QUESO::GslVector observations(obsSpace.zeroVector());
     
  //observations[0] = 0.182;
  //observations[1] = 0.522;
  observations[0] = 1.25;
  observations[1] = 1.66;
  observations[2] = 2.1; 
  observations[3] = 3.31;
  observations[4] = 4.75;
 
  QUESO::InterpolationSurrogateIOASCII<QUESO::GslVector, QUESO::GslMatrix>
    data_reader;
 
  QUESO::GslVector covariance(obsSpace.zeroVector());
     
  //covariance[0] = 0.00033124; 
  //covariance[1] = 0.00272484; 
  covariance[0] = 0.015625; 
  covariance[1] = 0.027556; 
  covariance[2] = 0.0441; 
  covariance[3] = 0.109561; 
  covariance[4] = 0.225625; 
  // Pass in observations to Gaussian likelihood object
  // Pass in observations to Gaussian likelihood object
    
  Likelihood<QUESO::GslVector, QUESO::GslMatrix> lhood("llhd_", paramDomain,
						       observations, covariance,env ,data_reader );
    
  QUESO::GslVector guess(paramSpace.zeroVector());
   /*
  guess[0] = 1.643613e+01;
  guess[1] =  3.868542e+01;
  guess[2] = 3.134539e+01;
    */
    
       
   if( env.subRank()  == 0 )
    {
    guess[2] =   25.5;
    guess[1] =  -29.0000;
    guess[0] =  -19.0000;
    }
   
      if( env.subRank() == 1 )
    {
    guess[2] = 26.6734;
    guess[1] =  -16.6667;
    guess[0] =  -13.3333;
    }
    
      if( env.subRank() == 2 )
    {
    guess[2] = 28.3468;
    guess[1] =  -3.3333;
    guess[0] =  -6.6667;
    
    }
    
      if( env.subRank() == 3 )
    {
    guess[2] = 30.0201;
    guess[1] =  10.0000;
    guess[0] =   0 ;
    }
    
    
      if( env.subRank() == 4 )
    {
    guess[2] = 31.6935;
    guess[1] =   23.3333;
    guess[0] =  6.6667;
    }
    
    
      if( env.subRank() == 5 )
    {
    guess[2] = 33.3668;
    guess[1] =   36.6667;
    guess[0] =  13.3333;
    }
    
    
      if( env.subRank() == 6 )
    {
    guess[2] = 38.3869;
    guess[1] =  50.0000;
    guess[0] =  20.0000;
    }
    
      if( env.subRank() == 7 )
    {
    guess[2] = 35.0402;
    guess[1] =  63.333;
    guess[0] =  26.6667;
    }
    
      if( env.subRank() == 8 )
    {
    guess[2] = 36.7135;
    guess[1] =  76.6667;
    guess[0] =  33.3333 ;
    }
    
      if( env.subRank() == 9 )
    {
    guess[2] = 39.8;
    guess[1] =  86.6667;
    guess[0] =  36;
    }
    
    
  QUESO::GslVector step_size(paramSpace.zeroVector());
  step_size[0] = 1;
  step_size[1] = 1;     
  step_size[2] = 1;

  QUESO::OptimizerMonitor monitor(paramSpace.env(),10000);
  monitor.set_display_output(true,true);

  QUESO::GslOptimizer optimizer(lhood);

  std::string solver_type = "nelder_mead";

  double h =  1.0e-8;
  optimizer.set_solver_type(solver_type);
  optimizer.set_step_size(step_size);
  optimizer.setFiniteDifferenceStepSize(h);

  if( env.fullRank() == 0 )
    {
      std::cout << std::endl
		<< "=============================================================" << std::endl
		<< "      Solving using: " << solver_type << std::endl
		<< "=============================================================" << std::endl;
    }

  optimizer.setInitialPoint(guess);

  optimizer.minimize(&monitor);

  const QUESO::GslVector& minimizer = optimizer.minimizer();
  unsigned int guess_size = 100;

  for( unsigned int i = 0; i < guess_size; i++ )
    {
      if( env.fullRank() == 0 )
	{
	  std::cout << "minimizer["<<i<<"] = " << minimizer[i] << std::endl;
	}
    }
       
   
  QUESO::GenericVectorRV<QUESO::GslVector, QUESO::GslMatrix>
    postRv("post_", paramSpace);
    
  QUESO::GslVector paramInitials(paramSpace.zeroVector());

  paramInitials[0] = minimizer[0];
  paramInitials[1] = minimizer[1];
  paramInitials[2] = minimizer[2];

  QUESO::GslMatrix proposalCovMatrix(paramSpace.zeroVector());

  for (unsigned int i = 0; i < 3; i++) {
    proposalCovMatrix(i, i) = 0.1;
  }
  
  QUESO::StatisticalInverseProblem<QUESO::GslVector,QUESO::GslMatrix> ip ("", NULL, priorRv, lhood, postRv);
  
  ip.solveWithBayesMetropolisHastings(NULL, paramInitials, &proposalCovMatrix);

  MPI_Finalize();
  
  return 0;
}

