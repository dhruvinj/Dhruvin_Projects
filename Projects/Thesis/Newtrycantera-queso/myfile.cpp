#include <queso/GslVector.h>
#include <queso/GslMatrix.h>
#include <queso/VectorSet.h>
#include <queso/BoxSubset.h>
#include <queso/UniformVectorRV.h>
#include <queso/GenericVectorRV.h>
#include <queso/GaussianLikelihoodScalarCovariance.h>
#include <queso/StatisticalInverseProblem.h>
#include "cantera/kinetics/Reaction.h" 
#include "cantera/oneD/Sim1D.h"
#include "cantera/oneD/Inlet1D.h"
#include "cantera/oneD/StFlow.h"
#include "cantera/IdealGasMix.h"
#include "cantera/transport.h"

template<class V, class M>
class Likelihood : public QUESO::GaussianLikelihoodScalarCovariance<V, M>
{
 protected:
  //mutable Cantera::IdealGasMix gas;
  //mutable Cantera::FreeFlame flow;
public:
	int flamespeed(double phi, double* fspeed, double param) const
{
    try {
        Cantera::IdealGasMix gas("inputfileedi.xml","gri30_mix");

        doublereal temp = 300.0; // K
        doublereal pressure = 1.0*Cantera::OneAtm; //atm
        doublereal uin=0.3; //m/sec

        gas.setState_TPX(temp, pressure, "O3:0.53, O2:0.47");
        size_t nsp = gas.nSpecies();

        Cantera::vector_fp x(nsp);

        doublereal C_atoms=0.0;
        doublereal H_atoms=0.0;
        doublereal ax=C_atoms+H_atoms/4.0;
        doublereal fa_stoic=1.0/(4.76*ax);
        for (size_t k=0; k<nsp; k++) {
            if (k==gas.speciesIndex("O3")) {
                x[k]=.530;
            } else if (k==gas.speciesIndex("O2")) {
                x[k]=0.47;
            }  else
                 {
                    x[k] = 0.0;
                 }
        }

        gas.setState_TPX(temp,pressure,DATA_PTR(x));
        doublereal rho_in=gas.density();

        Cantera::vector_fp yin(nsp);
        gas.getMassFractions(&yin[0]);

        try {
            gas.equilibrate("HP");
        } catch (Cantera::CanteraError& err) {
            std::cout << err.what() << std::endl;
        }
        
        Cantera::vector_fp yout(nsp);
        gas.getMassFractions(&yout[0]);
        doublereal rho_out = gas.density();
        doublereal Tad=gas.temperature();
        std::cout << phi<<' '<<Tad<<std::endl;
        std::tr1::shared_ptr<Cantera::Reaction> r2 = gas.reaction(2);


			Cantera::ElementaryReaction* e1;

			e1 = dynamic_cast<Cantera::ElementaryReaction*> (r2.get());

			if(e1 ==0) 
				{
				std::cout<< "Null pointer on type casting to derived";
				}

			std::tr1::shared_ptr<Cantera::ElementaryReaction> new_reaction;

			Cantera::Arrhenius new_rate(5.2e12,0.0,param);

 			new_reaction.reset( new Cantera::ElementaryReaction( e1->reactants, e1->products, new_rate ) );
 				

			gas.modifyReaction( 2, new_reaction );

        //=============  build each domain ========================


        //-------- step 1: create the flow -------------

        Cantera::FreeFlame flow(&gas);

        // create an initial grid
        int nz=5;
        doublereal lz=0.02;
        Cantera::vector_fp z(nz+1);
        doublereal dz=lz/((doublereal)(nz-1));
        for (int iz=0; iz<nz; iz++) {
            z[iz]=((doublereal)iz)*dz;
        }
        //add one node onto end of domain to help with zero gradient at outlet
        z[nz]=lz*1.05;
        nz++;

        flow.setupGrid(nz, &z[0]);

        // specify the objects to use to compute kinetic rates and
        // transport properties

        std::auto_ptr<Cantera::Transport> trmix(newTransportMgr("Mix", &gas));
        //std::auto_ptr<Cantera::Transport> trmulti(newTransportMgr("Multi", &gas));

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

        for (size_t i=0; i<nsp; i++) {
            value[0]=yin[i];
            value[1]=yout[i];
            value[2]=yout[i];
            flame.setInitialGuess(gas.speciesName(i),locs,value);
        }

        inlet.setMoleFractions(DATA_PTR(x));
        inlet.setMdot(mdot);
        inlet.setTemperature(temp);

        flame.showSolution();

        int flowdomain=1;
        double ratio=10.0;
        double slope=0.2;
        double curve=0.02;

        flame.setRefineCriteria(flowdomain,ratio,slope,curve);

        int loglevel=1;
        bool refine_grid = true;

        /* Solve freely propagating flame*/

        /* Linearly interpolate to find location where this
           temperature would exist. The temperature at this
           location will then be fixed for remainder of
           calculation.*/

        flow.fixTemperature();
        refine_grid=false;
        flame.setFixedTemperature(900.0);
        flame.solve(loglevel,refine_grid);
        refine_grid = true;
        flow.solveEnergyEqn();
        flame.solve(loglevel,refine_grid);
        double flameSpeed_mix = flame.value(flowdomain,flow.componentIndex("u"),0);
        std::cout << "Flame speed with mixture-averaged transport: " <<
             flame.value(flowdomain,flow.componentIndex("u"),0) << " m/s" << std::endl;
				/*
        // now switch to multicomponent transport
        flow.setTransport(*trmulti);
        flame.solve(loglevel, refine_grid);
        double flameSpeed_multi = flame.value(flowdomain,flow.componentIndex("u"),0);
        cout << "Flame speed with multicomponent transport: " <<
             flame.value(flowdomain,flow.componentIndex("u"),0) << " m/s" << endl;

        // now enable Soret diffusion
        flow.enableSoret(true);
        flame.solve(loglevel, refine_grid);
        double flameSpeed_full = flame.value(flowdomain,flow.componentIndex("u"),0);
        cout << "Flame speed with multicomponent transport + Soret: " <<
             flame.value(flowdomain,flow.componentIndex("u"),0) << " m/s" << endl;
				*/
        int np=flow.nPoints();
        std::vector<doublereal> zvec,Tvec,O2vec,O3vec,Uvec;

        printf("\n%9s\t%8s\t%5s\t%7s\n","z (m)", "T (K)", "U (m/s)", "Y(O3)");
        for (int n=0; n<np; n++) {
            Tvec.push_back(flame.value(flowdomain,flow.componentIndex("T"),n));
            O3vec.push_back(flame.value(flowdomain,flow.componentIndex("O3"),n));
            O2vec.push_back(flame.value(flowdomain,flow.componentIndex("O2"),n));
            Uvec.push_back(flame.value(flowdomain,flow.componentIndex("u"),n));
            zvec.push_back(flow.grid(n));
            printf("%9.6f\t%8.3f\t%5.3f\t%7.5f\n",flow.grid(n),Tvec[n],Uvec[n],O2vec[n]);
        }

        std::cout << std::endl<<"Adiabatic flame temperature from equilibrium is: "<<Tad<<std::endl;
        std::cout << "Flame speed for phi="<<phi<<" is "<<Uvec[0]<<" m/s."<<std::endl;
				*fspeed = Uvec[0];
        std::string reportFile = "flamespeed.csv";
        FILE* FP = fopen(reportFile.c_str(), "w");
        if (!FP) {
            printf("Failure to open file\n");
            exit(-1);
        }

        fprintf(FP," Flame speed (mixture-averaged      ) = %11.3e m/s\n", flameSpeed_mix);
       // fprintf(FP," Flame speed (multicomponent        ) = %11.3e m/s\n", flameSpeed_multi);
        //fprintf(FP," Flame speed (multicomponent + Soret) = %11.3e m/s\n", flameSpeed_full);
        fprintf(FP,"  Grid,   Temperature,   Uvec,   O2,    O3\n");
        for (int n = 0; n < np; n++) {
            fprintf(FP," %11.3e, %11.3e, %11.3e, %11.3e, %11.3e\n",
                    flow.grid(n), Tvec[n], Uvec[n], O2vec[n], O3vec[n]);
        }
        fclose(FP);
    } catch (Cantera::CanteraError& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << "program terminating." << std::endl;
        return -1;
    }
    return 0;
}
	
  Likelihood(const char * prefix, const QUESO::VectorSet<V, M> & domain,
      const V & observations, double variance)
    : QUESO::GaussianLikelihoodScalarCovariance<V, M>(prefix, domain,
        observations, variance)
  {
  }

  virtual ~Likelihood()
  {
  }

  virtual void evaluateModel(const V & domainVector, const V * domainDirection,
      V & modelOutput, V * gradVector, M * hessianMatrix,
      V * hessianEffect) const
  {
    // Evaluate model and fill up the m_modelOutput member variable
    for (unsigned int i = 0; i < modelOutput.sizeLocal(); i++) {
      //modelOutput[i] = 1.0;
      double* fspeed;
      fspeed = new double;
      	double param = domainVector[i];
				std::cout << "Current param = " <<  param << std::endl;
			 flamespeed(0.9,fspeed,param);
        modelOutput[i] = *fspeed;
    }
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



