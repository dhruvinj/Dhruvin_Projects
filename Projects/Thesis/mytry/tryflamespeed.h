#include "cantera/oneD/Sim1D.h"
#include "cantera/oneD/Inlet1D.h"
#include "cantera/oneD/StFlow.h"
#include "cantera/IdealGasMix.h"
#include "cantera/equilibrium.h"
#include "cantera/transport.h"

class tryflamespeed 
{

public:

int flamespeed(int np, void* p, double* fspeed, std::string filename) 
{

   //try {
        int i;
        Cantera::IdealGasMix*  mygas = new Cantera::IdealGasMix("dummy.xml","gri30_mix");
        
        doublereal temp = 300.0; // K
        doublereal pressure = 1.0*Cantera::OneAtm; //atm
        doublereal uin=0.3; //m/sec

        mygas->setState_TPX(temp, pressure, "O3:0.53, O2:0.47");
        size_t nsp = mygas->nSpecies();

        Cantera::vector_fp x(nsp);
			 double phi = 0.0;
        if (np > 0) {
            phi = *(double*)(p);
        }
        if (phi == 0.0) {
            std::cout << "Enter phi: ";
            std::cin >> phi;
        }
        for (size_t k=0; k<nsp; k++) {
            if (k==mygas->speciesIndex("O3")) {
                x[k]=.530;
            } else if (k==mygas->speciesIndex("O2")) {
                x[k]=0.47;
            }  else
                 {
                    x[k] = 0.0;
                 }
        }

        mygas->setState_TPX(temp,pressure,DATA_PTR(x));
        doublereal rho_in=mygas->density();

        Cantera::vector_fp yin(nsp);
        mygas->getMassFractions(&yin[0]);
        
        
         try {
            equilibrate(*mygas,"HP");
        } catch (Cantera::CanteraError& err) {
            std::cout << err.what() << std::endl;
        }
        
        Cantera::vector_fp yout(nsp);
        mygas->getMassFractions(&yout[0]);
        doublereal rho_out = mygas->density();
        doublereal Tad=mygas->temperature();
        std::cout << phi<<' '<<Tad<<std::endl;

   
        Cantera::FreeFlame* myflow  =  new Cantera::FreeFlame(mygas);

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

         myflow->setupGrid(nz, z);

        // specify the objects to use to compute kinetic rates and
        // transport properties

        Cantera::Transport* trmix = newTransportMgr("Mix", mygas);
        Cantera::Transport* trmulti = newTransportMgr("Multi", mygas);

         myflow->setTransport(*trmix);
         myflow->setKinetics(*mygas);
         myflow->setPressure(pressure);

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
        domains.push_back(myflow);
        domains.push_back(&outlet);

        //    OneDim flamesim(domains);

        Cantera::Sim1D* myflame = new Cantera::Sim1D(domains);

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
        myflame->setInitialGuess("u",locs,value);

        value[0]=temp;
        value[1]=Tad;
        value[2]=Tad;
        myflame->setInitialGuess("T",locs,value);

        for (i=0; i<nsp; i++) {
            value[0]=yin[i];
//            value[1]=yout[i];
//            value[2]=yout[i];
            value[1] = value[0];
            value[2] = value[0];
            myflame->setInitialGuess(mygas->speciesName(i),locs,value);
        }

        inlet.setMoleFractions(DATA_PTR(x));
        inlet.setMdot(mdot);
        inlet.setTemperature(temp);

        myflame->showSolution();

        int flowdomain=1;
        double ratio=10.0;
        double slope=0.2;
        double curve=0.02;
        double prune=-0.00005;

        myflame->setRefineCriteria(flowdomain,ratio,slope,curve,prune);

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

         myflow->fixTemperature();
        refine_grid=false;
        myflame->setFixedTemperature(900.0);
        //    flame.setAdiabaticFlame();
        myflame->solve(loglevel,refine_grid);
        refine_grid = true;
         myflow->solveEnergyEqn();
        myflame->solve(loglevel,refine_grid);
        double flameSpeed_mix = myflame->value(flowdomain, myflow->componentIndex("u"),0);
        std::cout << "Flame speed with mixture-averaged transport: " <<
             myflame->value(flowdomain, myflow->componentIndex("u"),0) << " m/s" << std::endl;

       

        np= myflow->nPoints();
        std::vector<doublereal> zvec,Tvec,O3vec,O2vec,Uvec;

        printf("\n%9s\t%8s\t%5s\t%7s\n","z (m)", "T (K)", "U (m/s)", "Y(O3)", "Y(O2)");
        for (int n=0; n<np; n++) {
            Tvec.push_back(myflame->value(flowdomain, myflow->componentIndex("T"),n));
            O3vec.push_back(myflame->value(flowdomain, myflow->componentIndex("O3"),n));
            O2vec.push_back(myflame->value(flowdomain, myflow->componentIndex("O2"),n));
            Uvec.push_back(myflame->value(flowdomain, myflow->componentIndex("u"),n));
            zvec.push_back( myflow->grid(n));
            printf("%9.6f\t%8.3f\t%5.3f\t%7.5f\n", myflow->grid(n),Tvec[n],Uvec[n],O3vec[n]);
        }

        std::cout << std::endl<<"Adiabatic flame temperature from equilibrium is: "<<Tad<<std::endl;
        std::cout << "Flame speed for phi="<<phi<<" is "<<Uvec[0]<<" m/s."<<std::endl;
				*fspeed= Uvec[0];
				
			 delete mygas;
       delete myflow;
       delete myflame; 
       
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
                     myflow->grid(n), Tvec[n], Uvec[n], O3vec[n], O2vec[n]);
                    
      
        }
        fclose(FP);
          
    //} catch (Cantera::CanteraError& err) {
       // std::cerr << err.what() << std::endl;
      //  std::cerr << "program terminating." << std::endl;
     //   return -1;
  //  }
   
}

};


