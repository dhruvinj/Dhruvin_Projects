//c++

#include <string>  
#include <sstream>
#include <fstream>
#include <cassert>    
#include <iostream>
#include <math.h>

// Boost
#include <boost/scoped_ptr.hpp>

//cantera headers
#include "cantera/oneD/Sim1D.h"
#include "cantera/oneD/Inlet1D.h"
#include "cantera/oneD/StFlow.h"
#include "cantera/IdealGasMix.h"
#include "cantera/equilibrium.h"
#include "cantera/transport.h"
// my model
#include "myflamespeed.h"

// QUESO
#include <queso/GslVector.h>
#include <queso/GslMatrix.h>
#include <queso/BoxSubset.h>
#include <queso/InterpolationSurrogateBuilder.h>
#include <queso/InterpolationSurrogateIOASCII.h>



template<class Vec,class Mat>
class ModelInterpolationBuilder : public QUESO::InterpolationSurrogateBuilder<Vec,Mat>
{

  
public:
  ModelInterpolationBuilder( QUESO::InterpolationSurrogateDataSet<Vec,Mat>& data, myflamespeed& model )
    : QUESO::InterpolationSurrogateBuilder<Vec,Mat>(data), _model(model), _count(0)

  {
  
  }

  virtual ~ModelInterpolationBuilder(){};

  virtual void evaluate_model( const Vec& domainVector,
			       std::vector<double>& values )
                                 
  {
    /*
    // Only print out progress indicator on rank 0
    if( this->_model.get_model().param_space().env().fullRank() == 0 )
    std::cout << "ModelInterpolationBuilder evaluation " << _count << std::endl;
    */
    //********************************************************************
    // Copy contents of domainVector to std::vector.
    // Doing this copy so we don't have to template the parameters class.
    //********************************************************************
    unsigned int num_params = domainVector.sizeGlobal();



    double param_1 = domainVector[0];
    double param_2 = domainVector[1];
				
    double flamespd =0; 
    
    int rank = this->m_data.get_dataset(0).get_paramDomain().env().worldRank(); 
    
    _model.flamespeed(0,0,flamespd, param_1 ,param_2, rank, _count );
    
    values[0] = flamespd;
       
    _count++;

  }
  
  // template class ModelInterpolationBuilder<QUESO::GslVector,QUESO::GslMatrix>; 
   
private:
  myflamespeed _model;

  unsigned int _count;

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

  {


    QUESO::FullEnvironment env(MPI_COMM_WORLD, argv[1], "", NULL);
    QUESO::VectorSpace<QUESO::GslVector, QUESO::GslMatrix> paramSpace(env, "param_", 2, NULL);
    QUESO :: GslVector paramMinValues ( paramSpace . zeroVector ());
    QUESO :: GslVector paramMaxValues ( paramSpace . zeroVector ());

    // the pre-exponential factor variation of O + O3 [=] O2 + O2 reaction(3)
    
    
    paramMinValues [0] = log(7.201e+10);
    paramMaxValues [0] = log(2.5e+17);
   
   
    // the activation energy variation of O + O3 [=] O2 + O2 reaction(3)
    paramMinValues [1] = 10;
    paramMaxValues [1] = 90;


    QUESO::BoxSubset<QUESO::GslVector, QUESO::GslMatrix> paramDomain("param_",paramSpace, paramMinValues, paramMaxValues);

    unsigned int n_datasets = 1;
    const std::vector<unsigned int> n_points(2,150);


    QUESO::InterpolationSurrogateDataSet<QUESO::GslVector, QUESO::GslMatrix>  data(paramDomain,  n_points,  n_datasets);

 
    myflamespeed gas;
 
 
    ModelInterpolationBuilder<QUESO::GslVector,QUESO::GslMatrix> builder( data, gas );

 
  
    builder.build_values();

    // Now that we've built the data, we write it out so we can reuse it later
    QUESO::InterpolationSurrogateIOASCII<QUESO::GslVector, QUESO::GslMatrix>
      data_writer;

    data_writer.write( "flamespeed_40.dat", data.get_dataset(0) );



  }

  MPI_Finalize();

  return 0;
}



































