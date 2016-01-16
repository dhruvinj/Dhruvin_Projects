#include<iostream>
#include<cmath>
#include<math.h>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<sstream>
#include "cantera/oneD/Sim1D.h"
#include "cantera/oneD/Inlet1D.h"
#include "cantera/oneD/StFlow.h"
#include "cantera/IdealGasMix.h"
#include "cantera/equilibrium.h"
#include "cantera/transport.h"
#include <sstream>
#include <fstream>
#include <cassert>

class myflamespeed 
{

 public:

  int flamespeed(int np, void* p, double& fspeed, double param_values_1, double param_values_2, int rank, int count)
  {
      std::stringstream rankstream;
      std::stringstream countstream;

      rankstream << rank ;
      countstream << count;
	
      std::string filename = "dummy_rank"+rankstream.str()+"_count"+countstream.str()+".xml";
    try {
    
    double a  = exp(param_values_1);
    
    
      std::stringstream ss_1;
      std::stringstream ss_2;
      ss_1  << a;
      ss_2  << param_values_2;
      

      //std::cout << "Current param = " <<  "+ss.str()+" << std::endl;

      std::string file =  "<?xml version=\"1.0\"?> \n <ctml> \n  <validate reactions=\"yes\" species=\"yes\"/>  \n  <!-- phase gri30_mix     -->  \n  <phase dim=\"3\" id=\"gri30_mix\"> \n     <elementArray datasrc=\"elements.xml\">O</elementArray> \n    <speciesArray datasrc=\"#species_data\"> \n     O  O2  O3   \n   </speciesArray> \n    <reactionArray datasrc=\"#reaction_data\"/>  \n   <state> \n      <temperature units=\"K\">300.0</temperature>  \n     <pressure units=\"Pa\">101325.0</pressure>  \n   </state>   \n  <thermo model=\"IdealGas\"/> \n    <kinetics model=\"GasKinetics\"/> \n    <transport model=\"Mix\"/>  \n </phase>  \n  <!-- species definitions     -->  \n <speciesData id=\"species_data\"> \n   <!-- species O    -->   \n  <species name=\"O\">   \n    <atomArray>O:1 </atomArray>    \n   <note>L 1/90</note>   \n    <thermo>  \n       <NASA Tmax=\"1000.0\" Tmin=\"200.0\" P0=\"100000.0\"> \n           <floatArray name=\"coeffs\" size=\"7\">     \n         3.168267100E+00,  -3.279318840E-03,   6.643063960E-06,  -6.128066240E-09,  \n             2.112659710E-12,   2.912225920E+04,   2.051933460E+00</floatArray>   \n      </NASA>   \n      <NASA Tmax=\"3500.0\" Tmin=\"1000.0\" P0=\"100000.0\">     \n       <floatArray name=\"coeffs\" size=\"7\">       \n       2.569420780E+00,  -8.597411370E-05,   4.194845890E-08,  -1.001777990E-11, \n              1.228336910E-15,   2.921757910E+04,   4.784338640E+00</floatArray>    \n     </NASA>  \n     </thermo>  \n     <transport model=\"gas_transport\">    \n     <string title=\"geometry\">atom</string>  \n       <LJ_welldepth units=\"K\">80.000</LJ_welldepth>  \n       <LJ_diameter units=\"A\">2.750</LJ_diameter>   \n      <dipoleMoment units=\"Debye\">0.000</dipoleMoment>    \n     <polarizability units=\"A3\">0.000</polarizability>  \n       <rotRelax>0.000</rotRelax>    \n   </transport> \n    </species>  \n    <!-- species O2    -->   \n  <species name=\"O2\">  \n     <atomArray>O:2 </atomArray>    \n   <note>TPIS89</note>      \n <thermo>     \n    <NASA Tmax=\"1000.0\" Tmin=\"200.0\" P0=\"100000.0\">  \n          <floatArray name=\"coeffs\" size=\"7\">    \n          3.782456360E+00,  -2.996734160E-03,   9.847302010E-06,  -9.681295090E-09,   \n            3.243728370E-12,  -1.063943560E+03,   3.657675730E+00</floatArray>    \n     </NASA>  \n       <NASA Tmax=\"3500.0\" Tmin=\"1000.0\" P0=\"100000.0\">       \n     <floatArray name=\"coeffs\" size=\"7\">      \n        3.282537840E+00,   1.483087540E-03,  -7.579666690E-07,   2.094705550E-10,        \n       -2.167177940E-14,  -1.088457720E+03,   5.453231290E+00</floatArray>   \n      </NASA>   \n    </thermo>  \n     <transport model=\"gas_transport\">   \n      <string title=\"geometry\">linear</string>  \n       <LJ_welldepth units=\"K\">107.400</LJ_welldepth>     \n    <LJ_diameter units=\"A\">3.460</LJ_diameter>   \n      <dipoleMoment units=\"Debye\">0.000</dipoleMoment>  \n       <polarizability units=\"A3\">1.600</polarizability>   \n      <rotRelax>3.800</rotRelax>   \n    </transport>  \n   </species> \n <!-- species O3    --> \n <species name=\"O3\"> \n <atomArray>O:3 </atomArray> \n <note>TPIS89</note> \n <thermo> \n <NASA Tmax=\"1000.0\" Tmin=\"200.0\" P0=\"100000.0\">  \n  <floatArray name=\"coeffs\" size=\"7\">  \n   2.46260900E+00, 9.58278100E-03, -7.08735900E-06, 1.36336800E-09,   \n  2.96964700E-13, 1.60615200E+04, 1.21418700E+01 </floatArray>\n </NASA>\n <NASA Tmax=\"3500.0\" Tmin=\"1000.0\" P0=\"100000.0\">  \n  <floatArray name=\"coeffs\" size=\"7\">   \n  5.42937100E+00, 1.82038000E-03, -7.70560700E-07,  1.49929300E-10, \n   -1.07556300E-14,  1.52352700E+04, -3.26638700E+00 </floatArray> \n </NASA> \n </thermo>  \n <transport model=\"gas_transport\"> \n <string title=\"geometry\">linear</string>  \n <LJ_welldepth units=\"K\">180</LJ_welldepth>  \n <LJ_diameter units=\"A\">4.1</LJ_diameter> \n <dipoleMoment units=\"Debye\">0.000</dipoleMoment> \n <polarizability units=\"A3\">0</polarizability> \n <rotRelax>2</rotRelax> \n </transport> \n </species> \n   </speciesData>  \n  <reactionData id=\"reaction_data\"> \n   <!-- reaction 0001    -->  \n   <reaction reversible=\"yes\" type=\"threeBody\" id=\"0001\">   \n    <equation>O + O [=] O2</equation>    \n   <rateCoeff>   \n      <Arrhenius>  \n          <A units=\"cm6/mol2/s\">4.35e+17</A>    \n        <b>-1.0</b>       \n     <E units=\"kJ/mol\">0.0</E>     \n    </Arrhenius>    \n     <efficiencies O3=\"0.92\" O2=\"0.94\" O=\"1.13\"></efficiencies>  \n     </rateCoeff>  \n     <reactants>O:2.0</reactants>   \n    <products>O2:1.0</products>   \n  </reaction>   \n   <!-- reaction 0002    -->   \n  <reaction reversible=\"yes\" type=\"threeBody\" id=\"0002\">   \n    <equation>O2 + O [=] O3</equation>   \n    <rateCoeff>    \n     <Arrhenius>     \n       <A units=\"cm6/mol2/s\"> 3.427e+13 </A>  \n          <b>0.0</b>      \n      <E units=\"kJ/mol\"> -4.234 </E>   \n      </Arrhenius>     \n    <efficiencies O3=\"0.92\" O2=\"0.94\" O=\"1.13\"></efficiencies>  \n     </rateCoeff>    \n   <reactants>O2:1.0 O:1.0</reactants>     \n  <products>O3:1.0</products>  \n   </reaction>    \n  <!-- reaction 0003    -->  \n   <reaction reversible=\"yes\" id=\"0003\">   \n    <equation>O + O3 [=] O2 + O2</equation>  \n     <rateCoeff>  \n       <Arrhenius>   \n             <A units=\"cm3/s/mol\">"+ss_1.str()+" </A>     \n       <b>0.0</b>   \n         <E units=\"kJ/mol\">"+ss_2.str()+"</E>    \n     </Arrhenius>   \n    </rateCoeff>   \n    <reactants>O:1.0 O3:1.0</reactants> \n      <products>O2:2.0</products>  \n   </reaction> \n </reactionData> \n </ctml> \n " ;                 
		 
      std::ofstream dummy;
 
      dummy.open(filename.c_str(), std::ios::out | std::ios::trunc );
	
      dummy << file ;
	
      dummy.close();
      dummy.flush();
    
    
      int i;
      Cantera::IdealGasMix gas(filename,"gri30_mix");
      /*
        std::cout << "Reaction 0: " << gas.reactionString(0) << std::endl
	<< "Reaction 1: " << gas.reactionString(1) << std::endl	
	<< "Reaction 2: " << gas.reactionString(2) << std::endl;
      */
      doublereal temp = 300.0; // K
      doublereal pressure = 1.0*Cantera::OneAtm; //atm
      doublereal uin=0.3; //m/sec

      gas.setState_TPX(temp, pressure, "O3:0.4, O2:0.6");
      int nsp = gas.nSpecies();

      Cantera::vector_fp x;
      x.resize(nsp);

      double phi = 0.9;
        
       
				
       
      for (int k=0; k<nsp; k++) {
	if (k==gas.speciesIndex("O3")) {
	  x[k]=0.4;
	} else if (k==gas.speciesIndex("O2")) {
	  x[k]=0.6;
	}
	else
	  {
	    x[k] = 0.0;
	  }
      }

      gas.setState_TPX(temp,pressure,DATA_PTR(x));
      doublereal rho_in=gas.density();

      double* yin=new double[nsp];
      double* xout=new double[nsp];


      gas.getMassFractions(yin);

      try {
	equilibrate(gas,"HP");
      } catch (Cantera::CanteraError& err) {
	std::cout << err.what() << std::endl;
  
      }

      double* yout=new double[nsp];
      gas.getMassFractions(yout);
      gas.getMoleFractions(xout);

      doublereal rho_out = gas.density();
      doublereal Tad=gas.temperature();
    //  std::cout << phi<<' '<<Tad<<std::endl;

      //double Tin=temp;
      //double Tout=Tad;
      //double breakpt=0.2;


      //=============  build each domain ========================


      //-------- step 1: create the flow -------------

      //AxiStagnFlow flow(&gas);
      Cantera::FreeFlame flow(&gas);

      // create an initial grid
      int nz=5;
      doublereal lz=0.02;
      doublereal* z=new double[nz+1];
      doublereal dz=lz/((doublereal)(nz-1));
      for (int iz=0; iz<nz; iz++) {
	z[iz]=((doublereal)iz)*dz;
      }
      //add one node onto end of domain to help with zero gradient at outlet
      z[nz]=lz*1.05;
      nz++;

      flow.setupGrid(nz, z);

      // specify the objects to use to compute kinetic rates and
      // transport properties

      Cantera::Transport* trmix = newTransportMgr("Mix", &gas);
      Cantera::Transport* trmulti = newTransportMgr("Multi", &gas);

      flow.setTransport(*trmix);
      flow.setKinetics(gas);
      flow.setPressure(pressure);

      //------- step 2: create the inlet  -----------------------

      Cantera::Inlet1D inlet;

      inlet.setMoleFractions(DATA_PTR(x));
      doublereal mdot=uin*rho_in;
      inlet.setMdot(mdot);
      inlet.setTemperature(temp);


      //------- step 3: create the outlet  ---------------------

      Cantera::Outlet1D outlet;

      //=================== create the container and insert the domains =====

      std::vector<Cantera::Domain1D*> domains;
      domains.push_back(&inlet);
      domains.push_back(&flow);
      domains.push_back(&outlet);

      //    OneDim flamesim(domains);

      Cantera::Sim1D flame(domains);

      //----------- Supply initial guess----------------------

      Cantera::vector_fp locs;
      Cantera::vector_fp value;

      locs.resize(3);
      value.resize(3);

      //ramp values from inlet to adiabatic flame conditions
      //  over 70% of domain and then level off at equilibrium
      double z1=0.7;

      double uout;
      uout=inlet.mdot()/rho_out;
      uin=inlet.mdot()/rho_in;
      locs[0]=0.0;
      locs[1]=z1;
      locs[2]=1.0;
      value[0]=uin;
      value[1]=uout;
      value[2]=uout;
      flame.setInitialGuess("u",locs,value);

      value[0]=temp;
      value[1]=Tad;
      value[2]=Tad;
      flame.setInitialGuess("T",locs,value);

      for (i=0; i<nsp; i++) {
	value[0]=yin[i];
	//            value[1]=yout[i];
	//            value[2]=yout[i];
	value[1] = value[0];
	value[2] = value[0];
	flame.setInitialGuess(gas.speciesName(i),locs,value);
      }

      inlet.setMoleFractions(DATA_PTR(x));
      inlet.setMdot(mdot);
      inlet.setTemperature(temp);

      // flame.showSolution();

      int flowdomain=1;
      double ratio=10.0;
      double slope=0.2;
      double curve=0.02;
      double prune=-0.00005;

      flame.setRefineCriteria(flowdomain,ratio,slope,curve,prune);

      int loglevel=0;
      bool refine_grid = true;

    

      flow.fixTemperature();
      refine_grid=false;
      flame.setFixedTemperature(900.0);
      //    flame.setAdiabaticFlame();
      flame.solve(loglevel,refine_grid);
      refine_grid = true;
      flow.solveEnergyEqn();
      flame.solve(loglevel,refine_grid);
      double flameSpeed_mix = flame.value(flowdomain,flow.componentIndex("u"),0);
  //    std::cout << "Flame speed with mixture-averaged transport: " <<
	//flame.value(flowdomain,flow.componentIndex("u"),0) << " m/s" << std::endl;

       

      int np=flow.nPoints();
      std::vector<doublereal> zvec,Tvec,O3vec,O2vec,Uvec;

      //     printf("\n%9s\t%8s\t%5s\t%7s\n","z (m)", "T (K)", "U (m/s)", "Y(O3)", "Y(O2)");
      for (int n=0; n<np; n++) {
	Tvec.push_back(flame.value(flowdomain,flow.componentIndex("T"),n));
	O3vec.push_back(flame.value(flowdomain,flow.componentIndex("O3"),n));
	O2vec.push_back(flame.value(flowdomain,flow.componentIndex("O2"),n));
	Uvec.push_back(flame.value(flowdomain,flow.componentIndex("u"),n));
	zvec.push_back(flow.grid(n));
	//  printf("%9.6f\t%8.3f\t%5.3f\t%7.5f\n",flow.grid(n),Tvec[n],Uvec[n],O3vec[n]);
      }

      // std::cout << std::endl<<"Adiabatic flame temperature from equilibrium is: "<<Tad<<std::endl;
     // std::cout << "Flame speed for phi="<<phi<<" is "<<Uvec[0]<<" m/s."<<std::endl;
      fspeed= Uvec[0];
      std::string reportFile = "flamespeed.csv";
      FILE* FP = fopen(reportFile.c_str(), "w");
      if (!FP) {
	//printf("Failure to open file\n");
	exit(-1);
      }


        
      if( remove( filename.c_str() ) != 0 )
	{
	 // perror( "Error deleting file" );
	}
      else
	{
	//  puts( "File successfully deleted" );
	}
    
      fclose(FP);
    } catch (Cantera::CanteraError& err) {
      std::cerr << err.what() << std::endl;
  //    std::cerr << "Flame speed calculation failed. Setting flame speed to -1.0" << std::endl;
      fspeed = -1.0;
      if( remove( filename.c_str() ) != 0 )
	{
	//  perror( "Error deleting file" );
	}
      return -1;
    }
    return 0;
  }

      
      
  //param *= 0.00831435; // Rescale to Kelvin
     
  
};
