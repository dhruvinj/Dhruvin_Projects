//-----------------------------------------------------------------------bl-
//-----------------------------------------------------------------------el-

// C++
#include <vector>

// Boost
#include "boost/scoped_ptr.hpp"

// NitCal
#include "model_interface_base.h"



namespace QUESO
{
  class BaseEnvironment;

  template<class V, class M>
  class InterpolationSurrogateIOASCII;

  template<class V, class M>
  class LinearLagrangeInterpolationSurrogate;
}

namespace NitridationCalibration
{
  template<class Vec,class Mat>
  class SurrogateModelComposition
  {
  public:

    SurrogateModelComposition( const QUESO::BaseEnvironment& queso_env)
    
    {
    
    unsigned int n_datasets =1;
    
    unsigned int n_datapoints = 2*n_datasets;
    
    
    // Now setup IO classes. These will hold the InterpolationSurrodateData we need for evaluation
    _interp_io.resize( n_datapoints );
    for( unsigned int d = 0; d < n_datasets; d++ )
      {
        std::string flamespeed_filename = dataset_names[d]+"../surrgatebuilder/flamespeed.dat";
        

        _interp_io[2*d] = new QUESO::InterpolationSurrogateIOASCII<Vec,Mat>;
        
        _interp_io[2*d]->read( flamespeed_filename, full_env, "");
       
      }

    // Now setup interpolation surrogates
    _interp_surrogate.resize( n_datapoints );
    for( unsigned int d = 0; d < n_datasets; d++ )
      {
        _interp_surrogate[2*d] =  new QUESO::LinearLagrangeInterpolationSurrogate<Vec,Mat>( _interp_io[2*d]->data() );

      }
    
    
    }

    ~SurrogateModelComposition();

    void compute_values( const Vec& param_values,
                         Vec& model_output ) const;

  

  protected:

    std::vector<QUESO::InterpolationSurrogateIOASCII<Vec,Mat>*> _interp_io;

    std::vector<QUESO::LinearLagrangeInterpolationSurrogate<Vec,Mat>*> _interp_surrogate;

  private:

    SurrogateModelComposition();

  };


#endif 

#endif 
