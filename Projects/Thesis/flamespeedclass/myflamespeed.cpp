int flamespeed(double phi, double* fspeed) const
{
    try {
         Cantera::IdealGasMix gas("/zoidberg1/data/users/dhruvinj/flamespeedtest/inputfileedi.xml","gri30_mix");

        doublereal temp = 300.0; // K
        doublereal pressure = 1.0*Cantera::OneAtm; //atm
        doublereal uin=0.3; //m/sec

        gas.setState_TPX(temp, pressure, "O3:0.53, O2:0.47");
        size_t nsp = gas.nSpecies();

        Cantera::vector_fp x(nsp);

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
        std::auto_ptr<Cantera::Transport> trmulti(newTransportMgr("Multi", &gas));

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


        int np=flow.nPoints();
        std::vector<doublereal> zvec,Tvec,O2vec,O3vec,Uvec;

        printf("\n%9s\t%8s\t%5s\t%7s\n","z (m)", "T (K)", "U (m/s)", "Y(O2)");
        for (int n=0; n<np; n++) {
            Tvec.push_back(flame.value(flowdomain,flow.componentIndex("T"),n));
            O2vec.push_back(flame.value(flowdomain,flow.componentIndex("O2"),n));
            O3vec.push_back(flame.value(flowdomain,flow.componentIndex("O3"),n));
            Uvec.push_back(flame.value(flowdomain,flow.componentIndex("u"),n));
            zvec.push_back(flow.grid(n));
            printf("%9.6f\t%8.3f\t%5.3f\t%7.5f\n",flow.grid(n),Tvec[n],Uvec[n],O2vec[n]);
        }

        std::cout << std::endl<<"Adiabatic flame temperature from equilibrium is: "<<Tad<<std::endl;
        std::cout << "Flame speed for phi="<<phi<<" is "<<Uvec[0]<<" m/s."<< std::endl;
				*fspeed = Uvec[0];	
        std::string reportFile = "flamespeed.csv";
        FILE* FP = fopen(reportFile.c_str(), "w");
        if (!FP) {
            printf("Failure to open file\n");
            exit(-1);
        }

        fprintf(FP," Flame speed (mixture-averaged      ) = %11.3e m/s\n", flameSpeed_mix);
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

/*

 try {
        IdealGasMix gas("/zoidberg1/data/users/dhruvinj/flamespeedtest/inputfileedi.xml","gri30_mix");

        doublereal temp = 300.0; // K
        doublereal pressure = 1.0*Cantera::OneAtm; //atm
        doublereal uin=0.3; //m/sec

        gas.setState_TPX(temp, pressure, "O3:0.53, O2:0.47");
        size_t nsp = gas.nSpecies();

        Cantera::vector_fp x(nsp);

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

        vector_fp yin(nsp);
        gas.getMassFractions(&yin[0]);
				
        try {
            gas.equilibrate("HP");
        } catch (CanteraError& err) {
            std::cout << err.what() << std::endl;
        }
        
        vector_fp yout(nsp);
        gas.getMassFractions(&yout[0]);
        doublereal rho_out = gas.density();
        doublereal Tad=gas.temperature();
        double phi = 0.9;
        cout << phi<<' '<<Tad<<endl;

        //=============  build each domain ========================


        //-------- step 1: create the flow -------------

        FreeFlame flow(&gas);

        // create an initial grid
        int nz=5;
        doublereal lz=0.02;
        vector_fp z(nz+1);
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

        std::auto_ptr<Transport> trmix(newTransportMgr("Mix", &gas));
        std::auto_ptr<Transport> trmulti(newTransportMgr("Multi", &gas));

        flow.setTransport(*trmix);
        flow.setKinetics(gas);
        flow.setPressure(pressure);

        //------- step 2: create the inlet  -----------------------

        Inlet1D inlet;

        inlet.setMoleFractions(DATA_PTR(x));
        doublereal mdot=uin*rho_in;
        inlet.setMdot(mdot);
        inlet.setTemperature(temp);


        //------- step 3: create the outlet  ---------------------

        Outlet1D outlet;

        //=================== create the container and insert the domains =====

        std::vector<Domain1D*> domains;
        domains.push_back(&inlet);
        domains.push_back(&flow);
        domains.push_back(&outlet);

        Sim1D flame(domains);

        //----------- Supply initial guess----------------------

        vector_fp locs;
        vector_fp value;

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
/*
        flow.fixTemperature();
        refine_grid=false;
        flame.setFixedTemperature(900.0);
        flame.solve(loglevel,refine_grid);
        refine_grid = true;
        flow.solveEnergyEqn();
        flame.solve(loglevel,refine_grid);
        double flameSpeed_mix = flame.value(flowdomain,flow.componentIndex("u"),0);
        cout << "Flame speed with mixture-averaged transport: " <<
             flame.value(flowdomain,flow.componentIndex("u"),0) << " m/s" << endl;

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

        int np=flow.nPoints();
        std::vector<doublereal> zvec,Tvec,COvec,CO2vec,Uvec;

        printf("\n%9s\t%8s\t%5s\t%7s\n","z (m)", "T (K)", "U (m/s)", "Y(CO)");
        for (int n=0; n<np; n++) {
            Tvec.push_back(flame.value(flowdomain,flow.componentIndex("T"),n));
            COvec.push_back(flame.value(flowdomain,flow.componentIndex("CO"),n));
            CO2vec.push_back(flame.value(flowdomain,flow.componentIndex("CO2"),n));
            Uvec.push_back(flame.value(flowdomain,flow.componentIndex("u"),n));
            zvec.push_back(flow.grid(n));
            printf("%9.6f\t%8.3f\t%5.3f\t%7.5f\n",flow.grid(n),Tvec[n],Uvec[n],COvec[n]);
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
        fprintf(FP," Flame speed (multicomponent        ) = %11.3e m/s\n", flameSpeed_multi);
        fprintf(FP," Flame speed (multicomponent + Soret) = %11.3e m/s\n", flameSpeed_full);
        fprintf(FP,"  Grid,   Temperature,   Uvec,   CO,    CO2\n");
        for (int n = 0; n < np; n++) {
            fprintf(FP," %11.3e, %11.3e, %11.3e, %11.3e, %11.3e\n",
                    flow.grid(n), Tvec[n], Uvec[n], COvec[n], CO2vec[n]);
        }
        fclose(FP);
    } catch (CanteraError& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << "program terminating." << endl;
       
    }
    */
