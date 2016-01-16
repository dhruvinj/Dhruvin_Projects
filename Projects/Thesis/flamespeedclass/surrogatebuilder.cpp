#include <string>       // std::string
//#include <iostream> 
#include "cantera/oneD/Sim1D.h"
#include "cantera/oneD/Inlet1D.h"
#include "cantera/oneD/StFlow.h"
#include "cantera/IdealGasMix.h"
#include "cantera/equilibrium.h"
#include "cantera/transport.h"
//#include <stdio.h>
#include "myflamespeed.h"
#include <sstream>
#include <fstream>
#include <cassert>
#include "nitcal_config.h"
#ifdef NITCAL_HAVE_QUESO
// This class
#include <model_interpolation_builder.h>

// QUESO
#include <queso/GslVector.h>
#include <queso/GslMatrix.h>


namespace NitridationCalibration
{
  template<class Vec,class Mat>
  ModelInterpolationBuilder<Vec,Mat>::ModelInterpolationBuilder( QUESO::InterpolationSurrogateDataSet<Vec,Mat>& data,
                                                                 const ModelEvaluatorBase<Vec,Mat>& model )
    : QUESO::InterpolationSurrogateBuilder<Vec,Mat>(data),
    _model(model),
    _count(0)
  {}

  template<class Vec,class Mat>
  void ModelInterpolationBuilder<Vec,Mat>::evaluate_model( const Vec& domainVector,
                                                           std::vector<double>& values )
  {
    // Only print out progress indicator on rank 0
    if( this->_model.get_model().param_space().env().fullRank() == 0 )
      std::cout << "ModelInterpolationBuilder evaluation " << _count << std::endl;

    //********************************************************************
    // Copy contents of domainVector to std::vector.
    // Doing this copy so we don't have to template the parameters class.
    //********************************************************************
    unsigned int num_params = domainVector.sizeGlobal();

    std::vector<double> param_values( num_params );
    for(unsigned int i = 0; i < num_params; i++ )
      {
	param_values[i] = domainVector[i];
      }

    _model.compute_values( param_values, values );

    _count++;
  }

  // Instantiate GSL version of this class
  template class ModelInterpolationBuilder<QUESO::GslVector,QUESO::GslMatrix>;

} // end namespace NitridationCalibration

#endif // NITCAL_HAVE_QUESO


int main(int argc, char ** argv) 

{


unsigned int n_datasets =1;
const std::vector<unsigned int> n_points(10000);


 int nodes = 100;
 double dx=0;
 
 dx = double(34.76-4.345)/double(nodes-1); 
std::vector<unsigned int> e1(nodes);	
	
double myspeed[nodes];	
e1[0] =4.345;
for(int i=1; i< nodes; i++){
e1[i] = e1[i-1] + dx ;
}

const BoxSubset<V,M> domain = e1 ; 
 int k = sizeof(e1)/sizeof(e1[0]);
 
 std::cout << k << std::endl; 
 int count =0;
 for(int z=0; z< k ; z++)
 {
 
   std::stringstream ss;
	ss  << e1[z];
	

//std::cout << "Current param = " <<  "+ss.str()+" << std::endl;

std::string file =  "<?xml version=\"1.0\"?> \n <ctml> \n  <validate reactions=\"yes\" species=\"yes\"/>  \n  <!-- phase gri30_mix     -->  \n  <phase dim=\"3\" id=\"gri30_mix\"> \n     <elementArray datasrc=\"elements.xml\">O</elementArray> \n    <speciesArray datasrc=\"#species_data\"> \n     O  O2  O3   \n   </speciesArray> \n    <reactionArray datasrc=\"#reaction_data\"/>  \n   <state> \n      <temperature units=\"K\">300.0</temperature>  \n     <pressure units=\"Pa\">101325.0</pressure>  \n   </state>   \n  <thermo model=\"IdealGas\"/> \n    <kinetics model=\"GasKinetics\"/> \n    <transport model=\"Mix\"/>  \n </phase>  \n  <!-- species definitions     -->  \n <speciesData id=\"species_data\"> \n   <!-- species O    -->   \n  <species name=\"O\">   \n    <atomArray>O:1 </atomArray>    \n   <note>L 1/90</note>   \n    <thermo>  \n       <NASA Tmax=\"1000.0\" Tmin=\"200.0\" P0=\"100000.0\"> \n           <floatArray name=\"coeffs\" size=\"7\">     \n         3.168267100E+00,  -3.279318840E-03,   6.643063960E-06,  -6.128066240E-09,  \n             2.112659710E-12,   2.912225920E+04,   2.051933460E+00</floatArray>   \n      </NASA>   \n      <NASA Tmax=\"3500.0\" Tmin=\"1000.0\" P0=\"100000.0\">     \n       <floatArray name=\"coeffs\" size=\"7\">       \n       2.569420780E+00,  -8.597411370E-05,   4.194845890E-08,  -1.001777990E-11, \n              1.228336910E-15,   2.921757910E+04,   4.784338640E+00</floatArray>    \n     </NASA>  \n     </thermo>  \n     <transport model=\"gas_transport\">    \n     <string title=\"geometry\">atom</string>  \n       <LJ_welldepth units=\"K\">80.000</LJ_welldepth>  \n       <LJ_diameter units=\"A\">2.750</LJ_diameter>   \n      <dipoleMoment units=\"Debye\">0.000</dipoleMoment>    \n     <polarizability units=\"A3\">0.000</polarizability>  \n       <rotRelax>0.000</rotRelax>    \n   </transport> \n    </species>  \n    <!-- species O2    -->   \n  <species name=\"O2\">  \n     <atomArray>O:2 </atomArray>    \n   <note>TPIS89</note>      \n <thermo>     \n    <NASA Tmax=\"1000.0\" Tmin=\"200.0\" P0=\"100000.0\">  \n          <floatArray name=\"coeffs\" size=\"7\">    \n          3.782456360E+00,  -2.996734160E-03,   9.847302010E-06,  -9.681295090E-09,   \n            3.243728370E-12,  -1.063943560E+03,   3.657675730E+00</floatArray>    \n     </NASA>  \n       <NASA Tmax=\"3500.0\" Tmin=\"1000.0\" P0=\"100000.0\">       \n     <floatArray name=\"coeffs\" size=\"7\">      \n        3.282537840E+00,   1.483087540E-03,  -7.579666690E-07,   2.094705550E-10,        \n       -2.167177940E-14,  -1.088457720E+03,   5.453231290E+00</floatArray>   \n      </NASA>   \n    </thermo>  \n     <transport model=\"gas_transport\">   \n      <string title=\"geometry\">linear</string>  \n       <LJ_welldepth units=\"K\">107.400</LJ_welldepth>     \n    <LJ_diameter units=\"A\">3.460</LJ_diameter>   \n      <dipoleMoment units=\"Debye\">0.000</dipoleMoment>  \n       <polarizability units=\"A3\">1.600</polarizability>   \n      <rotRelax>3.800</rotRelax>   \n    </transport>  \n   </species> \n <!-- species O3    --> \n <species name=\"O3\"> \n <atomArray>O:3 </atomArray> \n <note>TPIS89</note> \n <thermo> \n <NASA Tmax=\"1000.0\" Tmin=\"200.0\" P0=\"100000.0\">  \n  <floatArray name=\"coeffs\" size=\"7\">  \n   2.46260900E+00, 9.58278100E-03, -7.08735900E-06, 1.36336800E-09,   \n  2.96964700E-13, 1.60615200E+04, 1.21418700E+01 </floatArray>\n </NASA>\n <NASA Tmax=\"3500.0\" Tmin=\"1000.0\" P0=\"100000.0\">  \n  <floatArray name=\"coeffs\" size=\"7\">   \n  5.42937100E+00, 1.82038000E-03, -7.70560700E-07,  1.49929300E-10, \n   -1.07556300E-14,  1.52352700E+04, -3.26638700E+00 </floatArray> \n </NASA> \n </thermo>  \n <transport model=\"gas_transport\"> \n <string title=\"geometry\">linear</string>  \n <LJ_welldepth units=\"K\">180</LJ_welldepth>  \n <LJ_diameter units=\"A\">4.1</LJ_diameter> \n <dipoleMoment units=\"Debye\">0.000</dipoleMoment> \n <polarizability units=\"A3\">0</polarizability> \n <rotRelax>2</rotRelax> \n </transport> \n </species> \n   </speciesData>  \n  <reactionData id=\"reaction_data\"> \n   <!-- reaction 0001    -->  \n   <reaction reversible=\"yes\" type=\"threeBody\" id=\"0001\">   \n    <equation>O + O [=] O2</equation>    \n   <rateCoeff>   \n      <Arrhenius>  \n          <A units=\"cm6/mol2/s\">4.35e+17</A>    \n        <b>-1.0</b>       \n     <E units=\"kJ/mol\">0.0</E>     \n    </Arrhenius>    \n     <efficiencies O3=\"0.92\" O2=\"0.94\" O=\"1.13\"></efficiencies>  \n     </rateCoeff>  \n     <reactants>O:2.0</reactants>   \n    <products>O2:1.0</products>   \n  </reaction>   \n   <!-- reaction 0002    -->   \n  <reaction reversible=\"yes\" type=\"threeBody\" id=\"0002\">   \n    <equation>O2 + O [=] O3</equation>   \n    <rateCoeff>    \n     <Arrhenius>     \n       <A units=\"cm6/mol2/s\">3.427e+13</A>  \n          <b>0.0</b>      \n      <E units=\"kJ/mol\">-4.234</E>   \n      </Arrhenius>     \n    <efficiencies O3=\"0.92\" O2=\"0.94\" O=\"1.13\"></efficiencies>  \n     </rateCoeff>    \n   <reactants>O2:1.0 O:1.0</reactants>     \n  <products>O3:1.0</products>  \n   </reaction>    \n  <!-- reaction 0003    -->  \n   <reaction reversible=\"yes\" id=\"0003\">   \n    <equation>O + O3 [=] O2 + O2</equation>  \n     <rateCoeff>  \n       <Arrhenius>   \n         <A units=\"cm3/s/mol\">5.2e+12</A>     \n       <b>0.0</b>   \n         <E units=\"kJ/mol\">"+ss.str()+"</E>    \n     </Arrhenius>   \n    </rateCoeff>   \n    <reactants>O:1.0 O3:1.0</reactants> \n      <products>O2:2.0</products>  \n   </reaction> \n </reactionData> \n </ctml> \n " ;                 
 
  	std::ofstream dummy;
	std::stringstream count_stream;
	count_stream << count;
	
	std::string filename = "dummy"+count_stream.str()+".xml";
	
	
	  dummy.open(filename.c_str(), std::ios::out | std::ios::trunc );
	
	  dummy << file ;
	
	  dummy.close();
    dummy.flush();
    
      ss.str("");
	  
	  
	  	std::cout << "Current param = " <<  e1[z] << std::endl;
      double flamespd =0; 
      
         myflamespeed* mygas = new myflamespeed;
    
       mygas->flamespeed(0,0,&flamespd, filename);
    
    
   myspeed[z] = flamespd;    

    
       
       delete mygas;
       
     //std::remove( "dummy"+count_stream.str()+".xml") ; 
     
     if( remove( filename.c_str() ) != 0 )
     {
    perror( "Error deleting file" );
      }
      else
      {
    puts( "File successfully deleted" );
      }
    
     std::cout << "Flame speed = " << flamespd << std::endl;
	  

    count += 1;
	  }
	  
	  
	  for(int i= 0 ; i< nodes; i++)
	  {
	  
	  std::cout << "Flame speed = " << myspeed[i] << std::endl; 
	  }
	  /*
	  std::ofstream write_file("flamespeed.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
write_file.setf(std::ios::scientific);
write_file.precision(30);

assert(write_file.is_open());
for (int i=0; i< nodes; i++)
{

write_file << myspeed[i] << "\n";

}
write_file.close();


	  std::ofstream w_file("parameter.dat");
// Write numbers as +x.<13digits>e+00 (width 20)
w_file.setf(std::ios::scientific);
w_file.precision(30);

assert(w_file.is_open());
for (int i=0; i< nodes; i++)
{

w_file << e1[i] << "\n";

}
w_file.close();
*/


	  

  return 0;
}














