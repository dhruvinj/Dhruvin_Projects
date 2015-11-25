#include <queso/GslMatrix.h>
#include <queso/VectorSet.h>
#include <queso/BoxSubset.h>
#include <queso/UniformVectorRV.h>
#include <queso/GenericVectorRV.h>
#include <queso/GaussianLikelihoodScalarCovariance.h>
#include <queso/StatisticalInverseProblem.h>
#include "cantera/oneD/Sim1D.h"
#include "cantera/oneD/Inlet1D.h"
#include "cantera/oneD/StFlow.h"
#include "cantera/IdealGasMix.h"
#include "cantera/equilibrium.h"
#include "cantera/transport.h"
//#include "try1.h"
using std::cout;
using std::endl;

template<class V, class M>
class Likelihood : public QUESO::GaussianLikelihoodScalarCovariance<V, M>
{
 protected:
  mutable Cantera::IdealGasMix _gas;
  mutable Cantera::FreeFlame _flow;
 // Cantera::Transport* trmix;
 // Cantera::Transport* trmulti;
 // Cantera::Inlet1D inlet;
 // Cantera::Outlet1D outlet;     
 // std::vector<Cantera::Domain1D*> domains;
  // Cantera::Sim1D flame;
 // Cantera::vector_fp locs;
 // Cantera::vector_fp value;

public:
	//double flamespeed(int np, void* p, double param) const;
  Likelihood(const char * prefix, const QUESO::VectorSet<V, M> & domain,
      const V & observations, double variance)
    : QUESO::GaussianLikelihoodScalarCovariance<V, M>(prefix, domain,
						      observations, variance)
   
  {
        
      
  }

  virtual ~Likelihood()
  {
  }

  virtual void evaluateModel(const V & domainVector, const V * /*domainDirection*/,
      V & modelOutput, V * /*gradVector*/, M * /*hessianMatrix*/,
      V * /*hessianEffect*/) const
  {
    // Evaluate model and fill up the m_modelOutput member variable
    for (unsigned int i = 0; i < modelOutput.sizeLocal(); i++) {
    // fspeed = new double; 
	double param = domainVector[0];
	std::cout << "Current param = " <<  param << std::endl;
	std::cout.flush();
     double fspeed = this->flamespeed(0,0,param);
      modelOutput[i] = fspeed;
    }
  }

  double flamespeed(int np, void* p, double param) const 
    {
      //  try {
            int i;
          Cantera::IdealGasMix _gas("inputfileedi.xml","gri30_mix");

            doublereal temp = 300.0; // K
            doublereal pressure = 1.0*Cantera::OneAtm; //atm
            doublereal uin=0.3; //m/sec

            _gas.setState_TPX(temp, pressure, "O3:0.53, O2:0.47");
            int nsp = _gas.nSpecies();
            
             Cantera::vector_fp x;
             x.resize(nsp);

            double phi = 0.9;
           /* if (np > 0) {
                phi = *(double*)(p);
            }
            if (phi == 0.0) {
                cout << "Enter phi: ";
                std::cin >> phi;
            }*/

            doublereal C_atoms=0;
            doublereal H_atoms=0;
            doublereal ax=C_atoms+H_atoms/4.0;
            doublereal fa_stoic=1.0/(4.76*ax);
            for (int k=0; k<nsp; k++) {
                if (k==_gas.speciesIndex("O3")) {
                    x[k]=0.53;
                } else if (k==_gas.speciesIndex("O2")) {
                    x[k]=0.47;
                }
                else
                 {
                    x[k] = 0.0;
                 }
            }

            _gas.setState_TPX(temp,pressure,DATA_PTR(x));
            doublereal rho_in=_gas.density();

            double* yin=new double[nsp];
            double* xout=new double[nsp];


            _gas.getMassFractions(yin);

            try {
               equilibrate(_gas,"HP");
            } catch (Cantera::CanteraError& err) {
               std::cout << err.what() << std::endl;
            }
            double* yout=new double[nsp];
            _gas.getMassFractions(yout);
            _gas.getMoleFractions(xout);

            doublereal rho_out = _gas.density();
            doublereal Tad=_gas.temperature();
            cout << phi<<' '<<Tad<<endl;
            
            
            //double Tin=temp;
            //double Tout=Tad;
            //double breakpt=0.2;


            //=============  build each domain ========================


            //-------- step 1: create the flow -------------

            //AxiStagnFlow flow(&_gas);
            //Cantera::FreeFlame flow(&_gas);
            Cantera::FreeFlame _flow(&_gas);
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

            _flow.setupGrid(nz, z);

            // specify the objects to use to compute kinetic rates and
            // transport properties

           Cantera::Transport* trmix = newTransportMgr("Mix", &_gas);
           Cantera::Transport* trmulti = newTransportMgr("Multi", &_gas);

            _flow.setTransport(*trmix);
            _flow.setKinetics(_gas);
            _flow.setPressure(pressure);
            
            std::tr1::shared_ptr<Cantera::Reaction> r2 = _gas.reaction(2);

			Cantera::ElementaryReaction* e1;

			e1 = dynamic_cast<Cantera::ElementaryReaction*> (r2.get());

			if(e1 ==0) 
				{
				std::cout<< "Null pointer on type casting to derived";
				}

			std::tr1::shared_ptr<Cantera::ElementaryReaction> new_reaction;
				{
			Cantera::Arrhenius new_rate(5.2e12,0.0,param);

 			new_reaction.reset( new Cantera::ElementaryReaction( e1->reactants, e1->products, new_rate ) );
 				}

			_gas.modifyReaction( 2, new_reaction );

          

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
            domains.push_back(&_flow);
            domains.push_back(&outlet);

            //  OneDim flamesim(domains);

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
                flame.setInitialGuess(_gas.speciesName(i),locs,value);
            }

            inlet.setMoleFractions(DATA_PTR(x));
            inlet.setMdot(mdot);
            inlet.setTemperature(temp);

            flame.showSolution();

            int flowdomain=1;
            double ratio=10.0;
            double slope=0.2;
            double curve=0.02;
            double prune=-0.00005;

            flame.setRefineCriteria(flowdomain,ratio,slope,curve,prune);

            int loglevel=1;
            bool refine_grid = true;

            /* Solve species*/
            //flow.fixTemperature();
            //refine_grid=false;
            //flame.solve(loglevel,refine_grid);

            /* Solve freely propagating flame*/

            /* Linearly interpolate to find location where this
               temperature would exist. The temperature at this
               location will then be fixed for remainder of
               calculation.*/

            _flow.fixTemperature();
            refine_grid=false;
            flame.setFixedTemperature(900.0);
            //    flame.setAdiabaticFlame();
            flame.solve(loglevel,refine_grid);
            refine_grid = true;
            _flow.solveEnergyEqn();
            flame.solve(loglevel,refine_grid);
            double flameSpeed_mix = flame.value(flowdomain,_flow.componentIndex("u"),0);
            cout << "Flame speed with mixture-averaged transport: " <<
                 flame.value(flowdomain,_flow.componentIndex("u"),0) << " m/s" << endl;

            // now switch to multicomponent transport
            //flow.setTransport(*trmulti);
            //flame.solve(loglevel, refine_grid);
            //double flameSpeed_multi = flame.value(flowdomain,flow.componentIndex("u"),0);
            //cout << "Flame speed with multicomponent transport: " <<
              //   flame.value(flowdomain,flow.componentIndex("u"),0) << " m/s" << endl;

            // now enable Soret diffusion
            //flow.enableSoret(true);
            //flame.solve(loglevel, refine_grid);
            //double flameSpeed_full = flame.value(flowdomain,flow.componentIndex("u"),0);
            //cout << "Flame speed with multicomponent transport + Soret: " <<
               //  flame.value(flowdomain,flow.componentIndex("u"),0) << " m/s" << endl;

            np=_flow.nPoints();
            std::vector<doublereal> zvec,Tvec,O3vec,O2vec,Uvec;

            printf("\n%9s\t%8s\t%5s\t%7s\n","z (m)", "T (K)", "U (m/s)", "Y(O3)", "Y(O2)");
            for (int n=0; n<np; n++) {
                Tvec.push_back(flame.value(flowdomain,_flow.componentIndex("T"),n));
                O3vec.push_back(flame.value(flowdomain,_flow.componentIndex("O3"),n));
                O2vec.push_back(flame.value(flowdomain,_flow.componentIndex("O2"),n));
                Uvec.push_back(flame.value(flowdomain,_flow.componentIndex("u"),n));
                zvec.push_back(_flow.grid(n));
                printf("%9.6f\t%8.3f\t%5.3f\t%7.5f\n",_flow.grid(n),Tvec[n],Uvec[n],O3vec[n]);
            }

            cout << endl<<"Adiabatic flame temperature from equilibrium is: "<<Tad<<endl;
            cout << "Flame speed for phi="<<phi<<" is "<<Uvec[0]<<" m/s."<<endl;
             
            std::string reportFile = "flamespeed.csv";
            FILE* FP = fopen(reportFile.c_str(), "w");
            if (!FP) {
                printf("Failure to open file\n");
                exit(-1);
            }

            fprintf(FP," Flame speed (mixture-averaged      ) = %11.3e m/s\n", flameSpeed_mix);
            //fprintf(FP," Flame speed (multicomponent        ) = %11.3e m/s\n", flameSpeed_multi);
            //fprintf(FP," Flame speed (multicomponent + Soret) = %11.3e m/s\n", flameSpeed_full);
            fprintf(FP,"  Grid,   Temperature,   Uvec,   O3,    O2\n");
            for (int n = 0; n < np; n++) {
                fprintf(FP," %11.3e, %11.3e, %11.3e, %11.3e, %11.3e\n",
                        _flow.grid(n), Tvec[n], Uvec[n], O3vec[n], O2vec[n]);
            }
            fclose(FP);
           
         //  *fspeed = Uvec[0];
       // } catch (Cantera::CanteraError& err) {
          //  std::cerr << err.what() << std::endl;
        //    std::cerr << "program terminating." << endl;
        //    return -1;
     //   }
        return Uvec[0];
    }

  
};


int main(int argc, char ** argv) {
  MPI_Init(&argc, &argv);

  QUESO::FullEnvironment env(MPI_COMM_WORLD, argv[1], "", NULL);

  QUESO::VectorSpace<QUESO::GslVector, QUESO::GslMatrix> paramSpace(env,
      "param_", 1, NULL);

  double min_val = 4.345;
  double max_val = 34.76;

  QUESO::GslVector paramMins(paramSpace.zeroVector());
  paramMins.cwSet(min_val);
  QUESO::GslVector paramMaxs(paramSpace.zeroVector());
  paramMaxs.cwSet(max_val);

  QUESO::BoxSubset<QUESO::GslVector, QUESO::GslMatrix> paramDomain("param_",
      paramSpace, paramMins, paramMaxs);

  QUESO::UniformVectorRV<QUESO::GslVector, QUESO::GslMatrix> priorRv("prior_",
      paramDomain);

  // Set up observation space
  QUESO::VectorSpace<QUESO::GslVector, QUESO::GslMatrix> obsSpace(env,
      "obs_", 1, NULL);

  // Fill up observation vector
  QUESO::GslVector observations(obsSpace.zeroVector());
  observations[0] = 2.1;
 

  // Pass in observations to Gaussian likelihood object
  Likelihood<QUESO::GslVector, QUESO::GslMatrix> lhood("llhd_", paramDomain,
      observations, 1.0);

  QUESO::GenericVectorRV<QUESO::GslVector, QUESO::GslMatrix>
    postRv("post_", paramSpace);

  QUESO::StatisticalInverseProblem<QUESO::GslVector, QUESO::GslMatrix>
    ip("", NULL, priorRv, lhood, postRv);

  QUESO::GslVector paramInitials(paramSpace.zeroVector());

  paramInitials[0] = 17.38;

  QUESO::GslMatrix proposalCovMatrix(paramSpace.zeroVector());

  for (unsigned int i = 0; i < 1; i++) {
    proposalCovMatrix(i, i) = 0.1;
  }

  ip.solveWithBayesMetropolisHastings(NULL, paramInitials, &proposalCovMatrix);

  MPI_Finalize();

  return 0;
}

























